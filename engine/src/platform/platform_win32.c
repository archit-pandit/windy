#include "platform/platform.h"

// windows platform
#if WPLATFORM_WINDOWS
    #include "core/logger.h"

    #include <windows.h>
    #include <windowsx.h> // parameter input extraction

    #include <stdlib.h>

    typedef struct internal_state {
        HINSTANCE h_instance;
        HWND hwnd;
    } internal_state;

    // time
    static f64 clock_freq;
    static LARGE_INTEGER time_start;

    LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param) {
        switch (msg) {
            case WM_ERASEBKGND:
                // notif the OS that erasing will be handeld by app to prevent flickering
                return 1;

            case WM_CLOSE:
                //TODO: fire event to quit 
                return 0;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_SIZE: {
                // RECT r;
                // GetClientRect(hwnd, &r);

                // u32 width = r.right - r.left;
                // u32 height = r.bottom - r.top;

                // TODO: fire event for resize
            } break;

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP: {
                // b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
                // TODO: handle input
            } break;

            case WM_MOUSEMOVE : {
                // i32 x_pos = GET_X_LPARAM(l_param);
                // i32 y_pos = GET_Y_LPARAM(l_param);

                // // TODO: handle mouse input
            } break;

            case WM_MOUSEHWHEEL: {
                // i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);

                // if (z_delta != 0) {
                //     // flatten input to OS-INdependent (-1, 1)
                //     z_delta = (z_delta < 0) ? -1 : 1;
                // }

                // TODO: handle mouse wheel input
            } break;

            case WM_LBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP: {
                // b8 pressed = (msg == WM_LBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_RBUTTONDOWN);
                // TODO: handle button
            } break;
        }

        return DefWindowProcA(hwnd, msg, w_param, l_param);
    }

    b8 platform_startup(
        platform_state* p_state,
        const char* app_name,
        i32 x,
        i32 y,
        i32 width,
        i32 height
    ) {
        p_state->internal_state = malloc(sizeof(internal_state));
        internal_state* state = (internal_state*)p_state->internal_state;

        state->h_instance = GetModuleHandleA(0);

        // Windowing ---------------------------------------------------------------------------

        // setup + register win class
        HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);
        WNDCLASSA wc;
        memset(&wc, 0, sizeof(wc));
        wc.style = CS_DBLCLKS;  // Get double-clicks
        wc.lpfnWndProc = win32_process_message;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = state->h_instance;
        wc.hIcon = icon;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // NULL; // Manage the cursor manually
        wc.hbrBackground = NULL;                   // Transparent
        wc.lpszClassName = "windy_win_class";

        if (!RegisterClassA(&wc)) {
            MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return FALSE;
        }

        // create window

        // client window
        u32 c_x = x;
        u32 c_y = y;
        u32 c_width = width;
        u32 c_height = height;

        // full window
        u32 win_x = c_x;
        u32 win_y = c_y;
        u32 win_width = c_width;
        u32 win_height = c_height;

        u32 win_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
        u32 win_ex_style = WS_EX_APPWINDOW;

        win_style |= WS_MAXIMIZEBOX;
        win_style |= WS_MINIMIZEBOX;
        win_style |= WS_THICKFRAME;

        RECT border_rect = {0, 0, 0, 0};
        AdjustWindowRectEx(&border_rect, win_style, 0, win_ex_style);

        win_x += border_rect.left;
        win_y += border_rect.top;
        win_width += border_rect.right - border_rect.left;
        win_height += border_rect.bottom - border_rect.top;

        HWND handle = CreateWindowExA(
            win_ex_style, "windy_win_class", app_name,
            win_style, win_x, win_y, win_width, win_height,
            0, 0, state->h_instance, 0 
        );

        if (handle == 0) {
            MessageBoxA(NULL, "Window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            WFATAL("Window creation failed");

            return FALSE;
        } else {
            state->hwnd = handle;
        }

        b32 should_activate = 1; // TODO: should be false (0) if window shouldn't accept input
        i32 show_window_cmd_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;

        ShowWindow(state->hwnd, show_window_cmd_flags);

        // clock setup
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);

        clock_freq = 1.0 / (f64)freq.QuadPart;
        QueryPerformanceCounter(&time_start);

        return TRUE;
    }

    void platform_shutdown (platform_state* p_state) {
        internal_state* state = (internal_state*)p_state->internal_state;

        if (state->hwnd) {
            DestroyWindow(state->hwnd);
            state->hwnd = 0;
        }
    }

    b8 platform_pump_msgs(platform_state* p_state) {
        MSG msg;

        // process and dispatch messages from message stack
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        return TRUE;
    }

    // TODO: create custom/robust memory manipulators 
    void* platform_allocate(u64 size, b8 aligned)                       { return malloc(size); }
    void platform_free(void* block, b8 aligned)                         { free(block); }
    void* platform_zero_memory(void* block, u64 size)                   { return memset(block, 0, size); }
    void* platform_copy_memory(void* dest, const void* src, u64 size)   { return memcpy(dest, src, size); }
    void* platform_set_memory(void* dest, i32 val, u64 size)            { return memset(dest, val, size); }

    void platform_console_write(const char* msg, u8 colour) {
        HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

        // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
        static u8 lvls[6] = {64, 4, 6, 2, 1, 8};
        SetConsoleTextAttribute(console_handle, lvls[colour]);

        OutputDebugStringA(msg);

        u64 len = strlen(msg);
        LPDWORD num_written = 0;

        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)len, num_written, 0);
    }

    void platform_console_write_error(const char* msg, u8 colour) {
        HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);

        // FATAL, ERROR, WARN, INFO, DEBUG, TRACE
        static u8 lvls[6] = {64, 4, 6, 2, 1, 8};
        SetConsoleTextAttribute(console_handle, lvls[colour]);
        
        OutputDebugStringA(msg);

        u64 len = strlen(msg);
        LPDWORD num_written = 0;

        WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)len, num_written, 0);
    }

    f64 platform_get_abs_time() {
        LARGE_INTEGER time_now;
        QueryPerformanceCounter(&time_now);

        return (f64)time_now.QuadPart * clock_freq;
    }

    void platform_sleep(u64 ms) {
        Sleep(ms);
    }

#endif