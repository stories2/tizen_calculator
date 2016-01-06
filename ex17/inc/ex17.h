#ifndef __ex17_H__
#define __ex17_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <string.h>
#include <stdlib.h>


#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "ex17"

#if !defined(PACKAGE)
#define PACKAGE "org.example.ex17"
#endif

#endif /* __ex17_H__ */


static void calculate(char data[] , char screen_buffer[]);
static int check_permission(char );
static char pop(int *);
static void push(char ,int *);

static void clicked_reset_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_div_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_mul_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_del_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_7_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_8_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_9_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_diff_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_4_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_5_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_6_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_plus_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_1_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_2_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_3_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_equal_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_0_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_point_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_start_parent_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
static void clicked_end_parent_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
