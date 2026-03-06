// new_f133_version2_mainLogic.cc

#pragma once
#include "uart/ProtocolSender.h"
/*
*此文件由GUI工具生成
*文件功能:用于处理用户的逻辑相应代码
*功能说明:
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数,XXX代表GUI工具里面的[ID值]名称,
如Button1,当返回值为false的时候系统将不再处理这个按键,返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index)
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称,
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress)
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称,
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX()
当页面中存在滑动列表的时候,更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称,
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候,更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称,
如List1;pListItem 是贴图中的单条目对象,index是列表总目的偏移值。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mText1Ptr->setText("****") 在控件TextXXX上显示文字****
*mButton1Ptr->setSelected(true); 将控件mButton1设置为选中模式,图片会切换成选中图片,按钮文字会切换为选中后的颜色
*mSeekBarPtr->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1Ptr->refreshListView() 让mListView1 重新刷新,当列表数据变化后调用
*mDashbroadView1Ptr->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 "alt + /"  快捷键可以打开智能提示
*/

#include "net/context.h"
#include "link/context.h"
#include "uart/context.h"
#include "bt/context.h"
#include "media/audio_context.h"
#include "media/media_context.h"
#include "media/music_player.h"
#include "media/media_parser.h"
#include "system/setting.h"
#include "system/fm_emit.h"
#include "system/reverse.h"
#include "manager/LanguageManager.h"
#include "manager/ConfigManager.h"
#include "storage/StoragePreferences.h"
#include "misc/storage.h"
#include "fy/files.hpp"
#include "net/NetManager.h"
#include "os/MountMonitor.h"
#include "system/usb_monitor.h"
#include "tire/tire_parse.h"
#include "sysapp_context.h"
#include "utils/BitmapHelper.h"
#include <base/ui_handler.h>
#include "system/hardware.h"
#include <base/mount_notification.h>
#include <base/time.hpp>
#include "utils/TimeHelper.h"
#include "mode_observer.h"
#include "mcu_hash_checker.h"

#define WIFIMANAGER			NETMANAGER->getWifiManager()

// extern函数声明 - 同步其他界面的SeekBar
extern void set_navibar_brightnessBar(int progress);
extern void set_navibar_PlayVolSeekBar(int progress);
extern void set_ctrlbar_lightSeekBar(int progress);
extern void set_ctrlbar_volumSeekBar(int progress);
extern void setSettingFtu_BrillianceSeekBar(int progress);
extern void setSettingFtu_MediaSeekBar(int progress);

#define KEY_LONG_PRESS_TIMEOUT    3000
#define TIMER_POWERKEY_EVENT 	303
#define TIMER_POWERKEY_OFF		304

#define QUERY_LINK_AUTH_TIMER	3
#define SWITCH_ADB_TIMER	4
#define BT_MUSIC_ID3		5
#define MCU_AUTO_UPGRADE	6
#define MUSIC_ERROR_TIMER	20

#define TIME_SYNCED_FLAG "/data/.time_synced_flag"

#define SCREEN_WIDTH	1600  // 根据实际屏幕宽度调整 (用于滑动切换窗口)

extern void fold_statusbar();

static bt_cb_t _s_bt_cb;
static bool _s_need_reopen_linkview;
static int key_sec = 0;

// **内存优化:添加状态管理变量**
static bool _is_in_reverse_mode = false;      // 倒车状态
static bool _is_ui_update_paused = false;     // UI更新暂停状态
static bool _is_music_info_cached = false;    // 音乐信息缓存状态
static std::string _cached_title = "";        // 缓存的音乐标题
static std::string _cached_artist = "";       // 缓存的艺术家信息
static std::string _last_play_file = "";      // 上次播放的文件
static bool _background_resources_loaded = false; // 背景资源加载状态
static bool _is_exiting_reverse = false;      // 标记是否正在从倒车模式退出

// 当前页面索引
static int _current_page_index = 0;

// 页面切换时更新控件可见性
static void updatePageVisibility(int page) {
    _current_page_index = page;
    LOGD("[main] updatePageVisibility: page = %d", page);

    // 第一页控件: page1BluetoothTextView, page1CarPlayTextView, page1AndroidAutoTextView,
    //            page1MiracastTextView, page1AirPlayTextView
    bool page1Visible = (page == 0);
    if (mpage1BluetoothTextViewPtr) {
        mpage1BluetoothTextViewPtr->setVisible(page1Visible);
    }
    if (mpage1CarPlayTextViewPtr) {
        mpage1CarPlayTextViewPtr->setVisible(page1Visible);
    }
    if (mpage1AndroidAutoTextViewPtr) {
        mpage1AndroidAutoTextViewPtr->setVisible(page1Visible);
    }
    if (mpage1MiracastTextViewPtr) {
        mpage1MiracastTextViewPtr->setVisible(page1Visible);
    }
    if (mpage1AirPlayTextViewPtr) {
        mpage1AirPlayTextViewPtr->setVisible(page1Visible);
    }

    // 第二页控件: musicWindow, page2AudiooutputTextView, page2VideoTextView,
    //            page2AiCastTextView, musictext
    bool page2Visible = (page == 1);
    if (mmusicWindowPtr) {
        mmusicWindowPtr->setVisible(page2Visible);
    }
    if (mpage2AudiooutputTextViewPtr) {
        mpage2AudiooutputTextViewPtr->setVisible(page2Visible);
    }
    if (mpage2VideoTextViewPtr) {
        mpage2VideoTextViewPtr->setVisible(page2Visible);
    }
    if (mpage2AiCastTextViewPtr) {
        mpage2AiCastTextViewPtr->setVisible(page2Visible);
    }
    if (mmusictextPtr) {
        mmusictextPtr->setVisible(page2Visible);
    }

    // 第三页控件: page3PictureTextView
    bool page3Visible = (page == 2);
    if (mpage3PictureTextViewPtr) {
        mpage3PictureTextViewPtr->setVisible(page3Visible);
    }
}

static void init_default_language() {
    std::string current_code = LANGUAGEMANAGER->getCurrentCode();

    if (current_code.empty() || current_code == "zh_CN") {  // 当前语言代码为空、中文或系统首次启动的话就设置为英文
        if (!FILE_EXIST("/data/.language_init_flag")) {
            LOGD("First boot detected, setting default language to English");
            sys::setting::update_localescode("en_US");
            system("touch /data/.language_init_flag");
            LOGD("Default language set to English (en_US)");
        } else {  // 如果标志文件存在但语言仍是中文,不强制覆盖
            LOGD("Language init flag exists, current language: %s", current_code.c_str());
        }
    } else {
        LOGD("Current language already set: %s", current_code.c_str());
    }
}

static void check_mcu_auto_upgrade() {
    LOGD("[MAIN] Checking for MCU auto upgrade...");

    if(FILE_EXIST("/mnt/extsd/mcuautoupgrade")){
		EASYUICONTEXT->openActivity("setfactoryActivity");
	}
}

static void _register_timer_fun(int id, int time) {
	mActivityPtr->registerUserTimer(id, time);
}

static void _unregister_timer_fun(int id) {
	mActivityPtr->unregisterUserTimer(id);
}

static void entry_lylink_ftu() {
	if (!sys::reverse_does_enter_status()) {
		EASYUICONTEXT->openActivity("lylinkviewActivity");
		_s_need_reopen_linkview = false;
	} else {
		LOGD("Is reverse status !!!\n");
		lk::video_stop();
		_s_need_reopen_linkview = true;
	}
}

static void _lylink_callback(LYLINKAPI_EVENT evt, int para0, void *para1) {
	switch (evt) {
	case LYLINK_LINK_ESTABLISH:
		LOGD("LYLINK_LINK_ESTABLISH %s", lk::_link_type_to_str((LYLINK_TYPE_E) para0));
		EASYUICONTEXT->hideStatusBar();
		if (LINK_TYPE_AIRPLAY == para0 || LINK_TYPE_MIRACAST == para0 || LINK_TYPE_WIFILY == para0 || LINK_TYPE_WIFICP == para0) {
			if (bt::is_on()) {
				bt::power_off();
			}
			entry_lylink_ftu();
		}
		if(sys::setting::get_sound_mode() == E_SOUND_MODE_LINK){
			if(media::music_is_playing()){
				media::music_pause();
			}
		}
		break;
	case LYLINK_LINK_DISCONN:
		LOGD("LYLINK_LINK_DISCONN........... %s", lk::_link_type_to_str((LYLINK_TYPE_E) para0));
		if (LINK_TYPE_AIRPLAY == para0 || LINK_TYPE_MIRACAST == para0 || LINK_TYPE_WIFILY == para0 || LINK_TYPE_WIFICP == para0) {
			if (!bt::is_on()) {
				bt::power_on();
			}
		}
		bt::query_state();
		EASYUICONTEXT->closeActivity("lylinkviewActivity");
		break;
	case LYLINK_PHONE_CONNECT:
		LOGD("LYLINK_PHONE_CONNECT %s", lk::_link_type_to_str((LYLINK_TYPE_E) para0));
		if (para0 == LINK_TYPE_WIFIAUTO || para0 == LINK_TYPE_WIFICP) {
			LOGD("You should open AP now.");
		}
		break;
	case LYLINK_FOREGROUND:
		LOGD("LYLINK_FOREGROUND");
		entry_lylink_ftu();
		break;
	case LYLINK_BACKGROUND:
	case LYLINK_HID_COMMAND:{
		if (evt == LYLINK_BACKGROUND) {
			LOGD("[main] LYLINK_BACKGROUND\n");
		} else {
			LOGD("[main] LYLINK_HID_COMMAND");
		}

		const char *app = EASYUICONTEXT->currentAppName();
		if (app && (strcmp(app, "lylinkviewActivity") == 0)) {
			EASYUICONTEXT->goHome();
		} else {
			EASYUICONTEXT->closeActivity("lylinkviewActivity");
		}
		_s_need_reopen_linkview = false;
	}
		break;
	case LYLINK_PHONE_DISCONN:
		LOGD("LYLINK_PHONE_DISCONN............. %s", lk::_link_type_to_str((LYLINK_TYPE_E) para0));
		lylinkapi_gocsdk("IA\r\n", strlen("IA\r\n"));
		break;
	default:
		break;
	}
}

static void _reverse_status_cb(int status) {
	LOGD("reverse status %d\n", status);
	base::runInUiThreadUniqueDelayed("rear_view_detection", [](){
		int status = sys::reverse_does_enter_status();
		LOGD("[main] reverse_status %d\n", status);
		if (status == REVERSE_STATUS_ENTER) {
			EASYUICONTEXT->openActivity("reverseActivity");
		} else {
			EASYUICONTEXT->closeActivity("reverseActivity");
			if (_s_need_reopen_linkview) {
				_s_need_reopen_linkview = false;
				if (lk::is_connected()) {
					EASYUICONTEXT->openActivity("lylinkviewActivity");
				}
			}
		}

	}, 50);
}

static void parser() {
	std::string cur_play_file = media::music_get_current_play_file();

	// 如果文件没有改变且已缓存,直接使用缓存
	if (cur_play_file == _last_play_file && _is_music_info_cached && !_cached_title.empty()) {
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setText(_cached_title);
		}
		if (martistTextViewPtr) {
			martistTextViewPtr->setText(_cached_artist);
			martistTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
		}
		return;
	}

	_last_play_file = cur_play_file;

	id3_info_t info;
	memset(&info, 0, sizeof(id3_info_t));
	bool isTrue = media::parse_id3_info(cur_play_file.c_str(), &info);

	// 安全的字符串处理并缓存
	if (isTrue && info.title != nullptr && strlen(info.title) > 0) {
		_cached_title = std::string(info.title);
	} else {
		std::string file_name = fy::files::get_file_name(cur_play_file);
		if (isTrue && !file_name.empty()) {
			_cached_title = file_name;
		} else {
			_cached_title = "Unknown";
		}
	}

	if (isTrue && info.artist != nullptr && strlen(info.artist) > 0) {
		_cached_artist = std::string(info.artist);
	} else {
		_cached_artist = "Unknown";
	}

	// 更新UI
	if (mtitleTextViewPtr) {
		if (_cached_title == "Unknown") {
			mtitleTextViewPtr->setTextTr("Unknown");
		} else {
			mtitleTextViewPtr->setText(_cached_title);
		}
	}

	if (martistTextViewPtr) {
		if (_cached_artist == "Unknown") {
			martistTextViewPtr->setTextTr("Unknown");
		} else {
			martistTextViewPtr->setText(_cached_artist);
		}
		martistTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
	}

	_is_music_info_cached = true;
}

// 更新主界面音乐时间
static void update_main_music_time() {
    int curPos = -1;
    int maxPos = -1;

    if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
        if (media::music_get_play_index() != -1) {
            curPos = media::music_get_current_position() / 1000;
            maxPos = media::music_get_duration() / 1000;
        }
    } else if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_BT_MUSIC) {
        bt_music_t music_info = bt::get_music_info();
        curPos = music_info.curpos;
        maxPos = music_info.duration;

        static int last_valid_curPos = -1;
        static int last_valid_maxPos = -1;

        if (curPos >= 0) {
            last_valid_curPos = curPos;
        } else if (last_valid_curPos >= 0) {
            curPos = last_valid_curPos;
        }

        if (maxPos >= 0) {
            last_valid_maxPos = maxPos;
        } else if (last_valid_maxPos >= 0) {
            maxPos = last_valid_maxPos;
        }
    }
}

static void _update_music_info() {
	bt_music_t music_info = bt::get_music_info();
	if (mtitleTextViewPtr) {
		mtitleTextViewPtr->setText(music_info.title);
	}
	if (martistTextViewPtr) {
		martistTextViewPtr->setText(music_info.artist);
		martistTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
	}
}

static void _update_music_progress() {
	bt_music_t music_info = bt::get_music_info();

	if (mPlayProgressSeekbarPtr) {
		mPlayProgressSeekbarPtr->setMax(music_info.duration);
		mPlayProgressSeekbarPtr->setProgress(music_info.curpos);
	}
}

static void _bt_music_cb(bt_music_state_e state) {
	if (bt::music_is_playing()) {
		_update_music_info();
		_update_music_progress();
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
			mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
		}
		if (mButtonPlayPtr) {
			mButtonPlayPtr->setSelected(true);
		}
		sys::setting::set_music_play_dev(E_AUDIO_TYPE_BT_MUSIC);
		update_main_music_time();
	} else {
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
			mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
		}
		if (mButtonPlayPtr) {
			mButtonPlayPtr->setSelected(false);
		}
	}
}

static void _music_play_status_cb(music_play_status_e status) {
	switch (status) {
	case E_MUSIC_PLAY_STATUS_STARTED:
		parser();
		sys::setting::set_music_play_dev(E_AUDIO_TYPE_MUSIC);
		if (mButtonPlayPtr) {
			mButtonPlayPtr->setSelected(true);
		}
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
			mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
		}
		if (mPlayProgressSeekbarPtr) {
			mPlayProgressSeekbarPtr->setMax(media::music_get_duration() / 1000);
			mPlayProgressSeekbarPtr->setProgress(0);
		}
		update_main_music_time();
		break;
	case E_MUSIC_PLAY_STATUS_RESUME:
		parser();
		sys::setting::set_music_play_dev(E_AUDIO_TYPE_MUSIC);
		if (mPlayProgressSeekbarPtr) {
			mPlayProgressSeekbarPtr->setMax(media::music_get_duration() / 1000);
		}
		if (mButtonPlayPtr) {
			mButtonPlayPtr->setSelected(true);
		}
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
			mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
		}
		update_main_music_time();
		break;
	case E_MUSIC_PLAY_STATUS_STOP:
		if (mPlayProgressSeekbarPtr) {
			mPlayProgressSeekbarPtr->setMax(media::music_get_duration() / 1000);
		}
		if (mButtonPlayPtr) {
			mButtonPlayPtr->setSelected(false);
		}
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
			mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
			mtitleTextViewPtr->setTextTr("Unknown");
		}
		if (martistTextViewPtr) {
			martistTextViewPtr->setTextTr("Unknown");
		}
		_is_music_info_cached = false;
		_cached_title.clear();
		_cached_artist.clear();
		_last_play_file.clear();
		break;
	case E_MUSIC_PLAY_STATUS_PAUSE:
		if (mtitleTextViewPtr) {
			mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_NONE);
			mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
		}
		if (mButtonPlayPtr) {
			mButtonPlayPtr->setSelected(false);
		}
		break;
	case E_MUSIC_PLAY_STATUS_COMPLETED:
		LOGE("[main] music play completed, will play next\n");
		media::music_next();
		break;
	case E_MUSIC_PLAY_STATUS_ERROR:
		break;
	}
}

static void _bt_call_cb(bt_call_state_e state) {
	if (state != E_BT_CALL_STATE_IDLE) {
		if (lk::get_lylink_type() == LINK_TYPE_WIFIAUTO) {
			const char *app = EASYUICONTEXT->currentAppName();
			if (!app) return;
			if(strcmp(app, "reverseActivity") == 0) {
				_s_need_reopen_linkview = true;
			} else if(strcmp(app, "lylinkviewActivity") != 0) {
				EASYUICONTEXT->openActivity("lylinkviewActivity");
			}
		}
	}
}

static void _bt_add_cb() {
	_s_bt_cb.call_cb = _bt_call_cb;
	_s_bt_cb.music_cb = _bt_music_cb;
	bt::add_cb(&_s_bt_cb);
}

static void _bt_remove_cb() {
	bt::remove_cb(&_s_bt_cb);
}

static bool _show_sys_info(unsigned long *freeram) {
	struct sysinfo info;
	int ret = 0;
	ret = sysinfo(&info);
	if(ret != 0) {
		return false;
	}
	*freeram = info.freeram;
	return true;
}

static bool is_system_time_valid() {
    time_t now = time(nullptr);
    struct tm *t = localtime(&now);
    return (t->tm_year + 1900 >= 2020) || FILE_EXIST(TIME_SYNCED_FLAG);
}

static void ctrl_UI_init() {
	EASYUICONTEXT->hideStatusBar();
}

static void set_back_pic() {
}

// 更新所有控件的背景图片
static void update_all_backgrounds_for_mode() {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    LOGD("[main] update_all_backgrounds_for_mode() ENTER");

    bitmap_t *bg_bmp = NULL;

    // 1. 主背景
    BitmapHelper::loadBitmapFromFile(bg_bmp, CONFIGMANAGER->getResFilePath("/HomePage/carmain_home_wallpaper.jpg").c_str(), 3);
    LOGD("[main] Setting day mode background");
    if (mTextViewBgPtr) {
        mTextViewBgPtr->setBackgroundBmp(bg_bmp);
    }

//    // 2. musicTextViewWindow - media_bg
//    if (mmusicTextViewWindowPtr) {
//        mmusicTextViewWindowPtr->setBackgroundPic(CONFIGMANAGER->getResFilePath("/HomePage/media_bg_n.png").c_str());
//    }

    // 3. music progress background
    if (mPlayProgressSeekbarPtr && mTextView2Ptr) {
        mTextView2Ptr->setBackgroundPic(CONFIGMANAGER->getResFilePath("/HomePage/progress_n.png").c_str());
    }

    // 4. 更新appSlideWindow的子项图片
    if (mappSlideWindowPtr) {
        // index 0: CarPlay
        mappSlideWindowPtr->setItemStatusPic(0, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_carplay_n.png").c_str());
        // index 1: Android Auto
        mappSlideWindowPtr->setItemStatusPic(1, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_android_auto_n.png").c_str());
        // index 2: Bluetooth
        mappSlideWindowPtr->setItemStatusPic(2, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_bt_n.png").c_str());
        // index 3: AirPlay
        mappSlideWindowPtr->setItemStatusPic(3, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_airplay_n.png").c_str());
        // index 4: Miracast
        mappSlideWindowPtr->setItemStatusPic(4, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_miracast_n.png").c_str());
        // index 5: AiCast (LyLink)
        mappSlideWindowPtr->setItemStatusPic(5, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_aicast_n.png").c_str());
        // index 6: Music
        mappSlideWindowPtr->setItemStatusPic(6, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_music_n.png").c_str());
        // index 7: FM
        mappSlideWindowPtr->setItemStatusPic(7, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_audio_out_n.png").c_str());
        // index 8: Settings
        mappSlideWindowPtr->setItemStatusPic(8, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_set_n.png").c_str());
        // index 9: Video
        mappSlideWindowPtr->setItemStatusPic(9, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_video_n.png").c_str());
        // index 10: Photo Album
        mappSlideWindowPtr->setItemStatusPic(10, ZK_CONTROL_STATUS_NORMAL,
            CONFIGMANAGER->getResFilePath("/HomePage/icon_picture_n.png").c_str());
    }

    LOGD("[main] All backgrounds updated for day mode");

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
    LOGD("[main] update_all_backgrounds_for_mode() EXIT, elapsed time: %.3f seconds", elapsed_time);
}

static void _preload_resources() {
	const char *pic_tab[] = {
		"/res/font/sanswithfz_jp_it_pt.ttf",
		"navi/bg_bt_n.png",
		"navi/bg_bt_p.png",
		"navi/bg_eq_n.png",
		"navi/bg_eq_p.png",
		"navi/bg_fm_n.png",
		"navi/bg_fm_p.png",
		"navi/bg_screen_off_n.png",
		"navi/bg_screen_off_p.png",
		"navi/icon_btvoice.png",
		"navi/icon_light.png",
		"navi/icon_setting_n.png",
		"navi/icon_setting_p.png",
		"navi/icon_voice.png",
		"navi/progress_n.png",
		"navi/progress_p.png",
	};

	LOGD("[main] preload resources start\n");

	size_t size = TAB_SIZE(pic_tab);
	for (size_t i = 0; i < size; ++i) {
		if (i == 0) {
			fy::cache_file(pic_tab[i]);
		} else {
			fy::cache_file(CONFIGMANAGER->getResFilePath(pic_tab[i]));
		}
	}

	LOGD("[main] preload resources end\n");
}

static void key_status(bool down) {
	static bool is_down = false;
	static uint32_t mDownTime;
	mActivityPtr->unregisterUserTimer(TIMER_POWERKEY_EVENT);
	if (down) {
		if (!is_down) {
			is_down = true;
			mActivityPtr->registerUserTimer(TIMER_POWERKEY_OFF, 1000);
			return ;
		}
	} else {
		if (is_down) {
			if (sys::reverse_does_enter_status()) {
				LOGD("[main] is reverse status, don't proc screensaver\n");
				return ;
			}
			mActivityPtr->registerUserTimer(TIMER_POWERKEY_EVENT, 100);
		}
		is_down = false;
		mActivityPtr->unregisterUserTimer(TIMER_POWERKEY_OFF);
		key_sec = 0;
	}
}

// AppSlideWindow翻页监听器 - 支持3页
namespace {
class AppSlidePageChangeListener : public ZKSlideWindow::ISlidePageChangeListener {
protected:
	virtual void onSlidePageChange(ZKSlideWindow *pSlideWindow, int page) {
		LOGD("[main] AppSlidePageChangeListener: page changed to %d", page);
		// 根据页面设置对应的RadioButton
		switch (page) {
		case 0:
			mStatusRadioGroupPtr->setCheckedID(ID_MAIN_RadioButton0);
			break;
		case 1:
			mStatusRadioGroupPtr->setCheckedID(ID_MAIN_RadioButton1);
			break;
		case 2:
			mStatusRadioGroupPtr->setCheckedID(ID_MAIN_RadioButton2);
			break;
		default:
			mStatusRadioGroupPtr->setCheckedID(ID_MAIN_RadioButton0);
			break;
		}
		// 更新页面控件可见性
		updatePageVisibility(page);
	}
};
}
static AppSlidePageChangeListener _s_app_slide_page_change_listener;

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{1,  1000},
	{QUERY_LINK_AUTH_TIMER, 6000},
	{SWITCH_ADB_TIMER, 1000},
};

static void onUI_init() {
	_preload_resources();
	ctrl_UI_init();

    _is_in_reverse_mode = false;
    _is_ui_update_paused = false;
    _is_music_info_cached = false;
    _background_resources_loaded = false;
    _is_exiting_reverse = false;
    _cached_title.clear();
    _cached_artist.clear();
    _last_play_file.clear();
    _current_page_index = 0;

	sys::setting::init();
	sys::hw::init();

	uart::init();
	uart::set_amplifier_mute(0);
	uart::set_power_cr(1);
	uart::add_power_state_cb(key_status);

	bt::init();
	mActivityPtr->registerUserTimer(BT_MUSIC_ID3, 0);

	net::init();

	media::init();
	media::music_add_play_status_cb(_music_play_status_cb);

	lk::add_lylink_callback(_lylink_callback);
	lk::start_lylink();

	app::attach_timer(_register_timer_fun, _unregister_timer_fun);

	sys::reverse_add_status_cb(_reverse_status_cb);
	sys::reverse_detect_start();

	_bt_add_cb();
	bt::query_state();

	media::music_add_play_status_cb(_music_play_status_cb);
//	if (mTextView1Ptr) {
//		mTextView1Ptr->setTouchPass(true);
//	}
	if (martistTextViewPtr) {
		martistTextViewPtr->setTouchPass(true);
	}

	// 设置appSlideWindow的翻页监听器
	if (mappSlideWindowPtr) {
		mappSlideWindowPtr->setSlidePageChangeListener(&_s_app_slide_page_change_listener);
	}
	mStatusRadioGroupPtr->setCheckedID(ID_MAIN_RadioButton0);

	// 初始化页面可见性 - 默认显示第一页
	updatePageVisibility(0);

	if(bt::is_calling()){
		bt::call_vol(audio::get_lylink_call_vol());
	}

	base::UiHandler::implementTimerRegistration([]() {
		mActivityPtr->registerUserTimer(base::TIMER_UI_HANDLER, 0);
	});
}

static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
    }
}

static void onUI_show() {
	mode::set_switch_mode(E_SWITCH_MODE_NULL);
    LOGD("[main] Transitioning setup gannina");
    _is_ui_update_paused = false;
    _is_in_reverse_mode = false;

	int curPos = -1;

    // 更新所有背景(包括主背景和所有控件)
    update_all_backgrounds_for_mode();

	if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_BT_MUSIC) {
		_update_music_info();
		_update_music_progress();
		if (bt::music_is_playing()) {
			if (mButtonPlayPtr) {
				mButtonPlayPtr->setSelected(true);
			}
		}
		update_main_music_time();
	} else if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
		parser();
		if (media::music_is_playing()) {
			if (mButtonPlayPtr) {
				mButtonPlayPtr->setSelected(true);
			}
			curPos = media::music_get_current_position() / 1000;
			if (mPlayProgressSeekbarPtr) {
				mPlayProgressSeekbarPtr->setMax(media::music_get_duration() / 1000);
			}
			if (mtitleTextViewPtr) {
				mtitleTextViewPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
				mtitleTextViewPtr->setTextColor(0xFFFFFFFF);
			}
		}
		update_main_music_time();
	}
    if (curPos >= 0) {
    	if (mPlayProgressSeekbarPtr) {
    		mPlayProgressSeekbarPtr->setProgress(curPos);
    	}
    }
	if (!app::is_show_topbar()) {
		sys::setting::set_reverse_topbar_show(true);
		app::show_topbar();
	}
	init_default_language();
	check_mcu_auto_upgrade();

	if (mmusictextPtr) {
		mmusictextPtr->setLongMode(ZKTextView::E_LONG_MODE_SCROLL_CIRCULAR);
	}

	// 恢复页面可见性状态
	updatePageVisibility(_current_page_index);
}

static void onUI_hide() {
	struct timespec start_time, end_time;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	LOGD("[main] onUI_hide() ENTER");

	LOGD("[main] onUI_hide - cleaning up resources");
	_is_ui_update_paused = true;

	if (mTextViewBgPtr) {
		mTextViewBgPtr->setBackgroundBmp(NULL);
	}
//	if (mmusicTextViewWindowPtr) {
//		mmusicTextViewWindowPtr->setBackgroundPic(NULL);
//	}
	if (mToMusicPtr) {
		mToMusicPtr->setBackgroundPic(NULL);
	}

	_is_music_info_cached = false;
	_cached_title.clear();
	_cached_artist.clear();

	clock_gettime(CLOCK_MONOTONIC, &end_time);
	double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
	                      (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
	LOGD("[main] onUI_hide() EXIT, elapsed time: %.3f seconds", elapsed_time);
}

static void onUI_quit() {
	uart::remove_power_state_cb(key_status);
	lk::remove_lylink_callback(_lylink_callback);
	media::music_remove_play_status_cb(_music_play_status_cb);
	if (mPlayProgressSeekbarPtr) {
		mPlayProgressSeekbarPtr->setSeekBarChangeListener(NULL);
	}

	// 移除appSlideWindow的翻页监听器
	if (mappSlideWindowPtr) {
		mappSlideWindowPtr->setSlidePageChangeListener(NULL);
	}

	if (mTextViewBgPtr) {
		mTextViewBgPtr->setBackgroundBmp(NULL);
	}
//	if (mmusicTextViewWindowPtr) {
//		mmusicTextViewWindowPtr->setBackgroundPic(NULL);
//	}
	if (mToMusicPtr) {
		mToMusicPtr->setBackgroundPic(NULL);
	}

	_is_music_info_cached = false;
	_cached_title.clear();
	_cached_artist.clear();
	_last_play_file.clear();

	_bt_remove_cb();
}

static void onProtocolDataUpdate(const SProtocolData &data) {

}

static bool onUI_Timer(int id) {
	if (app::on_timer(id)) {
		return false;
	}
	switch (id) {
	case 0: {
		unsigned long freeram = 0;
		bool ret = _show_sys_info(&freeram);
		if(ret) {
			LOGD("-----------Current MemFree: %ldKB---------------", freeram >> 10);
		} else {
			LOGD("-----------get MemFree info fail----------------");
		}
	}
		break;
	case 1: {
        int curPos = -1;
        if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
            if (media::music_is_playing()) {
                curPos = media::music_get_current_position() / 1000;
            }
            if (curPos >= 0) {
            	if (mPlayProgressSeekbarPtr) {
            		mPlayProgressSeekbarPtr->setProgress(curPos);
            	}
            }
        }
        update_main_music_time();
	}
		break;
	case QUERY_LINK_AUTH_TIMER:
		lk::query_is_authorized();
		return false;
	case SWITCH_ADB_TIMER: {
		if (strcmp("UpgradeActivity", EASYUICONTEXT->currentAppName()) == 0) {
			app::hide_topbar();
		}
		if (sys::setting::is_usb_adb_enabled()) {
			if (sys::get_usb_mode() != E_USB_MODE_DEVICE) {
				sys::change_usb_mode(E_USB_MODE_DEVICE);
			}
		} else {
			sys::set_usb_config(E_USB_MODE_HOST);
		}
		uart::set_amplifier_mute(1);
	}
		return false;
	case BT_MUSIC_ID3:
		if (bt::music_is_playing()) {
			bt::query_music_info();
		}
		return false;
	case MUSIC_ERROR_TIMER:
		media::music_next(true);
		return false;
    case base::TIMER_UI_HANDLER:
      return base::UiHandler::onTimer();
      break;
	case TIMER_POWERKEY_EVENT:
		if (strcmp("screenOffActivity", EASYUICONTEXT->currentAppName()) == 0) {
			EASYUICONTEXT->closeActivity("screenOffActivity");
		} else {
			fold_statusbar();
	    	EASYUICONTEXT->openActivity("screenOffActivity");
		}
		return false;
	case TIMER_POWERKEY_OFF:{
		if ((key_sec++) >= 2) {
			if (sys::reverse_does_enter_status()) {
				LOGD("[main] is reverse status, don't proc key long press\n");
				key_sec = 0;
				return false;
			}
			if (lk::is_connected()) {
				lk::stop_lylink();
			}
			uart::app_turn_off();
		}
	}
		break;
	default:
		break;
	}
    return true;
}

/**
 * 检查触摸点是否在SeekBar区域内
 * 用于防止在操作SeekBar时误触发窗口切换
 */
static bool isTouchInSeekBarArea(int x, int y) {
	int margin = 20;  // 扩大检测区域，增加容错范围（上下左右各扩展20像素）

	// 检查播放进度SeekBar区域
	if (mPlayProgressSeekbarPtr && mPlayProgressSeekbarPtr->isVisible()) {
		LayoutPosition playPos = mPlayProgressSeekbarPtr->getPosition();
		if (x >= (playPos.mLeft - margin) && x <= (playPos.mLeft + playPos.mWidth + margin) &&
		    y >= (playPos.mTop - margin) && y <= (playPos.mTop + playPos.mHeight + margin)) {
			return true;
		}
	}

	// 检查ctrlbar是否显示，如果显示则检查触摸点是否在ctrlbar区域内
	// ctrlbar包含音量和亮度SeekBar，当它显示时禁止主界面的滑动切换
	if (app::is_show_ctrlbar()) {
		return true;
	}

	return false;
}

static bool onmainActivityTouchEvent(const MotionEvent &ev) {
	LayoutPosition pos = EASYUICONTEXT->getNaviBar()->getPosition();

	static MotionEvent down_ev;
	static bool allow_switch;

	if (pos.mTop != -pos.mHeight) {	return false; }
	switch (ev.mActionStatus) {
	case MotionEvent::E_ACTION_DOWN:
		if (app::is_hit_floatwnd(ev.mX, ev.mY))	{
			allow_switch = true;
			down_ev = ev;
		}
		break;
	case MotionEvent::E_ACTION_MOVE:
		break;
	case MotionEvent::E_ACTION_UP:
		break;
	default:
		break;
	}
	return false;
}

static bool onButtonClick_NextButton(ZKButton *pButton) {
    LOGD(" ButtonClick NextButton !!!\n");
	if (lk::is_connected()) {
		if (mlinkTipsWindowPtr) {
			mlinkTipsWindowPtr->showWnd();
		}
		return false;
	}
	if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
	    media::music_next(true);
	} else if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_BT_MUSIC) {
		bt::music_next();
	}
    return false;
}

static bool onButtonClick_ButtonPlay(ZKButton *pButton) {
    LOGD(" ButtonClick ButtonPlay !!!\n");

	if (lk::is_connected()) {
		if (mlinkTipsWindowPtr) {
			mlinkTipsWindowPtr->showWnd();
		}
		return false;
	}

	if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
	    if (media::music_get_play_index() == -1) {
	    	return false;
	    } else if (media::music_is_playing()) {
	        media::music_pause();
	    } else {
	    	media::music_resume();
	    }
	} else if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_BT_MUSIC) {
	    bt::music_is_playing() ? bt::music_pause() : bt::music_play();
	}
    return false;
}

static bool onButtonClick_PrevButton(ZKButton *pButton) {
    LOGD(" ButtonClick PrevButton !!!\n");
	if (lk::is_connected()) {
		if (mlinkTipsWindowPtr) {
			mlinkTipsWindowPtr->showWnd();
		}
		return false;
	}
	if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
	    media::music_prev(true);
	} else if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_BT_MUSIC) {
		bt::music_prev();
	}
    return false;
}

static void onProgressChanged_PlayProgressSeekbar(ZKSeekBar *pSeekBar, int progress) {
}

static bool onButtonClick_Setting(ZKButton *pButton) {
    LOGD(" ButtonClick Setting !!!\n");
    EASYUICONTEXT->openActivity("settingsActivity");
    return false;
}

static bool onButtonClick_ToMusic(ZKButton *pButton) {
    LOGD(" ButtonClick ToMusic !!!\n");
	if (lk::is_connected()) {
		if (mlinkTipsWindowPtr) {
			mlinkTipsWindowPtr->showWnd();
		}
		return false;
	}
    return false;
}

static void open_linkhelp_activity(link_mode_e mode) {
	Intent *i = new Intent;
	i->putExtra("link_mode", fy::format("%d", mode));
	LOGD("[main] choose link mode %s\n", sys::setting::get_link_mode_str(mode));
	EASYUICONTEXT->openActivity("linkhelpActivity", i);
}

static void _change_link_app(link_mode_e mode) {
	switch (mode) {
	case E_LINK_MODE_HICAR:
	case E_LINK_MODE_ANDROIDAUTO:
	case E_LINK_MODE_CARPLAY:
		if (net::get_mode() != E_NET_MODE_AP) { net::change_mode(E_NET_MODE_AP);}
		break;
	case E_LINK_MODE_AIRPLAY:
		if (net::get_mode() != E_NET_MODE_AP) { net::change_mode(E_NET_MODE_AP); }
		break;
	case E_LINK_MODE_CARLIFE:
		if (net::get_mode() != E_NET_MODE_WIFI) { net::change_mode(E_NET_MODE_WIFI); }
		break;
	case E_LINK_MODE_MIRACAST:
	case E_LINK_MODE_LYLINK:
		if (net::get_mode() != E_NET_MODE_P2P) { net::change_mode(E_NET_MODE_P2P); }
		break;
	default:
		break;
	}
	open_linkhelp_activity(mode);
}

static void open_link_activity(link_mode_e mode) {
	LYLINK_TYPE_E link_type = lk::get_lylink_type();
	switch(mode) {
	case E_LINK_MODE_CARPLAY:
		if ((link_type == LINK_TYPE_WIFICP) || (link_type == LINK_TYPE_USBCP)) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	case E_LINK_MODE_ANDROIDAUTO:
		if ((link_type == LINK_TYPE_WIFIAUTO) || (link_type == LINK_TYPE_USBAUTO)) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	case E_LINK_MODE_CARLIFE:
		if ((link_type == LINK_TYPE_WIFILIFE) || (link_type == LINK_TYPE_USBLIFE)) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	case E_LINK_MODE_HICAR:
		if ((link_type == LINK_TYPE_WIFIHICAR) || (link_type == LINK_TYPE_USBHICAR)) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	case E_LINK_MODE_MIRACAST:
		if (link_type == LINK_TYPE_MIRACAST) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	case E_LINK_MODE_LYLINK:
		if (link_type == LINK_TYPE_WIFILY) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	case E_LINK_MODE_AIRPLAY:
		if (link_type == LINK_TYPE_AIRPLAY) {
			EASYUICONTEXT->openActivity("lylinkviewActivity");
			return;
		}
		break;
	default:
		break;
	}
	if (lk::is_connected()) {
		if (mlinkTipsWindowPtr) {
			mlinkTipsWindowPtr->showWnd();
		}
		return;
	}

	if (mode == E_LINK_MODE_AIRPLAY || mode == E_LINK_MODE_LYLINK || mode ==E_LINK_MODE_MIRACAST) {
		if (bt::is_on()) {
			bt::power_off();
		}
	} else {
		if (!bt::is_on()) {
			bt::power_on();
		}
	}

	open_linkhelp_activity(mode);
}

static bool onButtonClick_Button1(ZKButton *pButton) {
    LOGD(" ButtonClick Button1 !!!\n");
    EASYUICONTEXT->openActivity("mcubtUpdActivity");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    LOGD(" ButtonClick Button2 !!!\n");
    EASYUICONTEXT->openActivity("soundEffectActivity");
    return false;
}

static void onCheckedChanged_StatusRadioGroup(ZKRadioGroup* pRadioGroup, int checkedID) {
    LOGD(" RadioGroup StatusRadioGroup checked %d", checkedID);

    int page = 0;
    switch (checkedID) {
    case ID_MAIN_RadioButton0:
        page = 0;
        break;
    case ID_MAIN_RadioButton1:
        page = 1;
        break;
    case ID_MAIN_RadioButton2:
        page = 2;
        break;
    default:
        page = 0;
        break;
    }

    // 切换SlideWindow到对应页面
//    if (mappSlideWindowPtr) {
//        mappSlideWindowPtr->turnToPage(page);
//    }

    // 更新页面控件可见性
    updatePageVisibility(page);
}

static void onProgressChanged_PlayVolSeekBar(ZKSeekBar *pSeekBar, int progress) {
}

static bool onButtonClick_button_apps(ZKButton *pButton) {
    LOGD(" ButtonClick button_apps !!!\n");
    return false;
}

static void onCheckedChanged_RadioGroup1(ZKRadioGroup* pRadioGroup, int checkedID) {
    LOGD(" RadioGroup RadioGroup1 checked %d", checkedID);
}

static void onCheckedChanged_page3RadioGroup(ZKRadioGroup* pRadioGroup, int checkedID) {
    LOGD(" RadioGroup page3RadioGroup checked %d", checkedID);
}

static bool onButtonClick_audiooutput3Button(ZKButton *pButton) {
    LOGD(" ButtonClick audiooutput3Button !!!\n");
    return false;
}

static bool onButtonClick_toLocalmusicButton(ZKButton *pButton) {
    LOGD(" ButtonClick toLocalmusicButton !!!\n");
    if (lk::is_connected()) {
		if (mlinkTipsWindowPtr) {
			mlinkTipsWindowPtr->showWnd();
		}
		return false;
	}
    // 只有当音源为本地音乐时才跳转到musicActivity
    if (sys::setting::get_music_play_dev() == E_AUDIO_TYPE_MUSIC) {
        EASYUICONTEXT->openActivity("musicActivity");
    }
    return false;
}

static void onSlideItemClick_appSlideWindow(ZKSlideWindow *pSlideWindow, int index) {
    LOGD(" onSlideItemClick_ appSlideWindow %d !!!\n", index);
    switch(index) {
    case 0:  // CarPlay
        LOGD(" ButtonClick CPButton !!!\n");
        open_link_activity(E_LINK_MODE_CARPLAY);
        break;
    case 1:  // Android Auto
        LOGD(" ButtonClick AAButton !!!\n");
        open_link_activity(E_LINK_MODE_ANDROIDAUTO);
        break;
    case 3:  // AirPlay
        LOGD(" ButtonClick APButton !!!\n");
        open_link_activity(E_LINK_MODE_AIRPLAY);
        break;
    case 5:  // AiCast (LyLink)
        LOGD(" ButtonClick ACButton !!!\n");
        open_link_activity(E_LINK_MODE_LYLINK);
        break;
    case 4:  // Miracast
        LOGD(" ButtonClick MCButton !!!\n");
        open_link_activity(E_LINK_MODE_MIRACAST);
        break;
    case 2:  // Bluetooth
        LOGD(" ButtonClick BtMusicButton !!!\n");
        if (lk::is_connected()) {
            if (mlinkTipsWindowPtr) {
                mlinkTipsWindowPtr->showWnd();
            }
            break;
        }
        EASYUICONTEXT->openActivity("btsettingActivity");
        break;
    case 6:  // Music
        LOGD(" ButtonClick MusicButton !!!\n");
        if (lk::is_connected()) {
            if (mlinkTipsWindowPtr) {
                mlinkTipsWindowPtr->showWnd();
            }
            break;
        }
        EASYUICONTEXT->openActivity("musicActivity");
        break;
    case 9:  // Video
        LOGD(" ButtonClick VideoButton !!!\n");
        if (lk::is_connected()) {
            if (mlinkTipsWindowPtr) {
                mlinkTipsWindowPtr->showWnd();
            }
            break;
        }
        EASYUICONTEXT->openActivity("videoActivity");
        break;
    case 10:  // Photo Album
        LOGD(" ButtonClick PhotoAlbum !!!\n");
        if (lk::is_connected()) {
            if (mlinkTipsWindowPtr) {
                mlinkTipsWindowPtr->showWnd();
            }
            break;
        }
        EASYUICONTEXT->openActivity("PhotoAlbumActivity");
        break;
    case 8:  // Settings
        LOGD(" ButtonClick setting !!!\n");
        EASYUICONTEXT->openActivity("setshowActivity");
        break;
    case 7:  // FM
        LOGD(" ButtonClick FM !!!\n");
        EASYUICONTEXT->openActivity("FMemitActivity");
        break;
    default:
        break;
    }
}
