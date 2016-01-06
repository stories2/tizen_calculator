/*
 * click_event.c
 *
 *  Created on: Dec 2, 2015
 *      Author: stori
 */
#include "ex17.h"
#include "progress.c"

static char screen_buffer[200];

static void
clicked_reset_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"");
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_div_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s/",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_mul_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s*",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_del_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   int str_length = strlen(screen_buffer);
   if(str_length > 0)
   {
	   screen_buffer[str_length-1] = '\0';
   }
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_7_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s7",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_8_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s8",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_9_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s9",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_diff_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s-",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_4_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s4",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_5_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s5",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_6_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s6",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_plus_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s+",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_1_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s1",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_2_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s2",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_3_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s3",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_equal_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s=",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);

   dlog_print(DLOG_INFO,"ex17","start calculate");

   calculate(screen_buffer,screen_buffer);

   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_0_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s0",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_point_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s.",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_start_parent_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s(",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}

static void
clicked_end_parent_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *entry = data;
   sprintf(screen_buffer,"%s)",screen_buffer);
   elm_entry_entry_set(entry, screen_buffer);
}
