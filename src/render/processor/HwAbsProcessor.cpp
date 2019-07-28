/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "../include/HwAbsProcessor.h"
#include "HwPair.h"

HwAbsProcessor::HwAbsProcessor(string name) : Object(), name(name) {
    pipeline = new UnitPipeline(name);
    provider = new HwModelProvider(ALIAS_OF_MODEL_PROVIDER);
    registerAnUnit(provider);
}

HwAbsProcessor::~HwAbsProcessor() {
    if (pipeline) {
        pipeline->release();
        delete pipeline;
        pipeline = nullptr;
    }
    provider = nullptr;
    onDestroy();
}

void HwAbsProcessor::onDestroy() {

}

void HwAbsProcessor::registerAnUnit(Unit *unit) {
    if (pipeline) {
//        if(!provider){
//            Logcat::e("HWVC", "HwAbsProcessor::registerAnUnit failed. You must create an pipeline model.");
//            return;
//        }
        unit->setModelProvider(provider);
        pipeline->registerAnUnit(unit);
    } else {
        Logcat::e("HWVC",
                  "HwAbsProcessor::registerAnUnit failed. You must call startPipeline first.");
    }
}

void HwAbsProcessor::postEvent(Message *msg) {
    if (pipeline) {
        pipeline->postEvent(msg);
    } else {
        Logcat::e("HWVC", "Please call startPipeline first.");
        Logcat::i("HWVC", "HwAbsProcessor skip message %p", msg);
    }
}

void HwAbsProcessor::post(function<void()> runnable) {
    if (runnable) {
        Message *msg = new Message(0, [runnable](Message *msg2) {
            msg2->runnable = nullptr;
            runnable();
        });
        postEvent(msg);
    }
}

HwPairBuilder<int32_t> *HwAbsProcessor::putInt32(string key, int32_t value) {
    return new HwPairBuilder<int32_t>(HwPair<string, int32_t>(key, value),
                                      [this](string target, HwPair<string, int32_t> *hwPair) {
                                          Message *msg = new Message(
                                                  HwModelProvider::EVENT_PUT_INT32, nullptr,
                                                  Message::QUEUE_MODE_FIRST_ALWAYS, nullptr);
                                          msg->obj = new HwPair<string, int32_t>(
                                                  target + "_" + hwPair->key(), hwPair->value());
                                          this->postEvent(msg);
                                      });
}

void HwAbsProcessor::putInt64(string unitAlias, string key, int64_t value) {
    Message *msg = new Message(HwModelProvider::EVENT_PUT_INT64, nullptr,
                               Message::QUEUE_MODE_FIRST_ALWAYS, nullptr);
    msg->obj = new HwPair<string, int64_t>(unitAlias + "_" + key, value);
    postEvent(msg);
}

void HwAbsProcessor::putString(string unitAlias, string key, string value) {
    Message *msg = new Message(HwModelProvider::EVENT_PUT_STRING, nullptr,
                               Message::QUEUE_MODE_FIRST_ALWAYS, nullptr);
    msg->obj = new HwPair<string, string>(unitAlias + "_" + key, value);
    postEvent(msg);
}

void HwAbsProcessor::putObject(string unitAlias, string key, Object *value) {
    Message *msg = new Message(HwModelProvider::EVENT_PUT_OBJECT, nullptr,
                               Message::QUEUE_MODE_FIRST_ALWAYS, nullptr);
    msg->obj = new HwPair<string, Object *>(unitAlias + "_" + key, value);
    postEvent(msg);
}