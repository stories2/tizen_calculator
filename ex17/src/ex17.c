#include "ex17.h"
#include <dlog.h>
#include "click_event.c"

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
	Evas_Object *background;
	Evas_Object *grid;
	Evas_Object *entry;
	Evas_Object *panel;
	Evas_Object *basic_view;
} appdata_s;


extern char screen_buffer[200];

static void (*event_func[20])(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
		= {clicked_reset_cb,clicked_div_cb,clicked_mul_cb,clicked_del_cb,clicked_7_cb,
				clicked_8_cb,clicked_9_cb,clicked_diff_cb,clicked_4_cb,clicked_5_cb,
				clicked_6_cb,clicked_plus_cb,clicked_1_cb,clicked_2_cb,clicked_3_cb,
				clicked_equal_cb,clicked_0_cb,clicked_point_cb,clicked_start_parent_cb,
				clicked_end_parent_cb};

static Evas_Object * create_basic_content(Evas_Object *sub_grid,appdata_s *ad);

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

static Evas_Object *
create_entry(Evas_Object *grid)
{
	Evas_Object *entry;

	entry = elm_entry_add(grid);
	elm_entry_editable_set(entry,EINA_FALSE);
	elm_entry_entry_set(entry,"<font_size = 50><align = right></font_size>");
	evas_object_show(entry);

	return entry;
}

static Evas_Object *
create_conform(Evas_Object *conform)
{
	Evas_Object *form,*background;
	if(conform == NULL)
	{
		dlog_print(DLOG_INFO,"ex17","form is null");
		return NULL;
	}
	else
	{
		form = elm_conformant_add(conform);
		evas_object_size_hint_weight_set(form,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
		elm_win_resize_object_add(conform,form);

		background = elm_bg_add(form);
		elm_object_style_set(background,"indicator/headerbg");
		elm_object_part_content_set(form,"elm.swallow.indicator_bg",background);
		evas_object_show(background);

		evas_object_show(form);
		return form;
	}
}

static Evas_Object *
create_background(Evas_Object *win)
{
	Evas_Object *background;
	if(win == NULL)
	{
		dlog_print(DLOG_INFO,"ex17","window is null");
		return NULL;
	}
	else
	{
		background = elm_bg_add(win);
		evas_object_size_hint_weight_set(background,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
		elm_win_resize_object_add(win,background);
		evas_object_show(background);
		return background;
	}
}

static Evas_Object *
create_panel(Evas_Object *grid , appdata_s *ad)//parent ad
{
	Evas_Object *board , *sub_grid; //panel,grid

	board = elm_panel_add(grid);
	elm_panel_orient_set(board,ELM_PANEL_ORIENT_BOTTOM);
	evas_object_show(board);

	sub_grid = elm_grid_add(board);
	evas_object_size_hint_weight_set(sub_grid,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(sub_grid,EVAS_HINT_FILL,EVAS_HINT_FILL);
	elm_object_content_set(board,sub_grid);

	ad->basic_view = create_basic_content(sub_grid,ad);
	evas_object_size_hint_weight_set(ad->basic_view,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->basic_view,EVAS_HINT_FILL,EVAS_HINT_FILL);
	elm_grid_pack(sub_grid,ad->basic_view,3,3,94,94);

	return board;
}

static Evas_Object *
create_basic_content(Evas_Object *sub_grid,appdata_s *ad)//parent ad
{
	Evas_Object *table_view , *button;
	table_view = elm_table_add(sub_grid);
	elm_table_padding_set(table_view,10,10);

	char button_txt[21][6] = {{"Reset"},{"/"},{"*"},{"Del"},{"7"},{"8"},{"9"},
			{"-"},{"4"},{"5"},{"6"},{"+"},{"1"},{"2"},{"3"},{"="},{"0"},{"."},
			{"("},{")"}
	};

	int i,t,q = 0;
	char buffer[100];
	for(i=0;i<5;i+=1)
	{
		for(t=0;t<4;t+=1)
		{
			button = elm_button_add(table_view);
			evas_object_size_hint_weight_set(button,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(button,EVAS_HINT_FILL,EVAS_HINT_FILL);
			sprintf(buffer,"<font_size = 50>%s</font_size>",button_txt[q]);
			elm_object_text_set(button,buffer);
			//evas_object_smart_callback_add(button, "clicked", clicked_divide_cb, ad->entry);
			evas_object_smart_callback_add(button,"clicked",event_func[q],ad->entry);
			q+=1;
			evas_object_show(button);
			elm_table_pack(table_view,button,t,i,1,1);
		}
	}
	evas_object_show(table_view);

	return table_view;
}

static void
create_base_gui(appdata_s *ad)
{
	/* Window */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	sprintf(screen_buffer,"");

	ad->background = create_background(ad->win);
	ad->conform = create_conform(ad->win);

	elm_win_conformant_set(ad->win,EINA_TRUE);
	elm_win_indicator_mode_set(ad->win,ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win,ELM_WIN_INDICATOR_OPAQUE);

	ad->grid = elm_grid_add(ad->conform);
	evas_object_size_hint_weight_set(ad->grid,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ad->grid,EVAS_HINT_FILL,EVAS_HINT_FILL);
	elm_object_content_set(ad->conform,ad->grid);

	ad->entry = create_entry(ad->grid);
	elm_grid_pack(ad->grid,ad->entry,5,5,90,25);

	ad->panel = create_panel(ad->grid,ad);
	elm_grid_pack(ad->grid,ad->panel,0,35,100,65);

	evas_object_show(ad->win);
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;

	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
