//
// Created by aluno on 24/10/18.
//

#include "init.h"

std::unique_ptr<Database> dbInstance = std::make_unique<Database>();
EventHandler globalHandler = EventHandler();

void EventHandler::registerOnUpdate(CallbackFunction callback) {
    EventHandler::callbacks.push_back(callback);
}

void EventHandler::callUpdate() {
    for (const auto &func: callbacks) {
        func();
    }
}
