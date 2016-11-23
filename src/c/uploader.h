#pragma once

#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1

void worker_message_handler(uint16_t type, AppWorkerMessage *message);
void perform_happiness_upload(int answers[]);