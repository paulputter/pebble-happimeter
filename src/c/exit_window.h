#pragma once
#define EXIT_WINDOW_MESSAGE "Do you really want to exit?"
void exit_window_create();
void exit_window_destroy();
void setNumberOfWindow(int n);
Window *exit_window_get_window();