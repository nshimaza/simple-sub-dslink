/*
 * 
 * Copyright (c) 2016,2018 Cisco and/or its affiliates.
 *
 * This software is licensed to you under the terms of the Cisco Sample
 * Code License, Version 1.0 (the "License"). You may obtain a copy of the
 * License at
 *
 *                https://developer.cisco.com/docs/licenses
 *
 * All use of the material herein must be in accordance with the terms of
 * the License. All rights not expressly granted by the License are
 * reserved. Unless required by applicable law or agreed to separately in
 * writing, software distributed under the License is distributed on an "AS
 * IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied.
 */

#include <stdio.h>
#include <stdlib.h>

#define LOG_TAG "main"

#include <dslink/requester.h>
#include <dslink/log.h>

static char* nodePath = NULL;


// Called to initialize your node structure.
void on_init(DSLink* link) {
    (void) link;
    log_info("Initialized!\n");
}

// Called when the DSLink is connected.
void on_connected(DSLink* link) {
    (void) link;
    log_info("Connected!\n");
}

// Called when the DSLink is disconnected.
// If this was not initiated by dslink_close,
// then a reconnection attempt is made.
void on_disconnected(DSLink* link) {
    (void) link;
    log_info("Disconnected!\n");
}

void on_value_update(DSLink* link, uint32_t sid, json_t* val, json_t* ts) {
    (void) link;
    (void) sid;
    (void) ts;
    printf("%s\n", json_string_value(val));
}

void on_requester_ready(DSLink* link) {
    dslink_requester_subscribe(link, nodePath, on_value_update, 1);
}


int main(int argc, char* argv[])
{
    (void) argc;
    const char* linkName = "SimpleSubDSLink";
    nodePath = argv[1];
    char* dslink_argv[] = { argv[0], argv[2] };

    DSLinkCallbacks cbs = {
            on_init,
            on_connected,
            on_disconnected,
            on_requester_ready
    };

    return dslink_init(2, dslink_argv, linkName, /* isRequester */ 1, /* isResponder */ 0, &cbs);
}
