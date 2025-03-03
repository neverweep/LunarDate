// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

int lunarYear;
int lunarMonth;
int lunarDay;
int solarYear;
int solarMonth;
int solarDay;
int cyclicalYear;
int cyclicalMonth;
int cyclicalDay;
bool isLeapMonth;
bool isLeapYear;

// 农历数据
static const int lunarInfo[] = {
        0x4bd8, 0x4ae0, 0xa570, 0x54d5, 0xd260, 0xd950, 0x5554, 0x56af,
        0x9ad0, 0x55d2, 0x4ae0, 0xa5b6, 0xa4d0, 0xd250, 0xd295, 0xb54f,
        0xd6a0, 0xada2, 0x95b0, 0x4977, 0x497f, 0xa4b0, 0xb4b5, 0x6a50,
        0x6d40, 0xab54, 0x2b6f, 0x9570, 0x52f2, 0x4970, 0x6566, 0xd4a0,
        0xea50, 0x6a95, 0x5adf, 0x2b60, 0x86e3, 0x92ef, 0xc8d7, 0xc95f,
        0xd4a0, 0xd8a6, 0xb55f, 0x56a0, 0xa5b4, 0x25df, 0x92d0, 0xd2b2,
        0xa950, 0xb557, 0x6ca0, 0xb550, 0x5355, 0x4daf, 0xa5b0, 0x4573,
        0x52bf, 0xa9a8, 0xe950, 0x6aa0, 0xaea6, 0xab50, 0x4b60, 0xaae4,
        0xa570, 0x5260, 0xf263, 0xd950, 0x5b57, 0x56a0, 0x96d0, 0x4dd5,
        0x4ad0, 0xa4d0, 0xd4d4, 0xd250, 0xd558, 0xb540, 0xb6a0, 0x95a6,
        0x95bf, 0x49b0, 0xa974, 0xa4b0, 0xb27a, 0x6a50, 0x6d40, 0xaf46,
        0xab60, 0x9570, 0x4af5, 0x4970, 0x64b0, 0x74a3, 0xea50, 0x6b58,
        0x5ac0, 0xab60, 0x96d5, 0x92e0, 0xc960, 0xd954, 0xd4a0, 0xda50,
        0x7552, 0x56a0, 0xabb7, 0x25d0, 0x92d0, 0xcab5, 0xa950, 0xb4a0,
        0xbaa4, 0xad50, 0x55d9, 0x4ba0, 0xa5b0, 0x5176, 0x52bf, 0xa930,
        0x7954, 0x6aa0, 0xad50, 0x5b52, 0x4b60, 0xa6e6, 0xa4e0, 0xd260,
        0xea65, 0xd530, 0x5aa0, 0x76a3, 0x96d0, 0x4afb, 0x4ad0, 0xa4d0,
        0xd0b6, 0xd25f, 0xd520, 0xdd45, 0xb5a0, 0x56d0, 0x55b2, 0x49b0,
        0xa577, 0xa4b0, 0xaa50, 0xb255, 0x6d2f, 0xada0, 0x4b63, 0x937f,
        0x49f8, 0x4970, 0x64b0, 0x68a6, 0xea5f, 0x6b20, 0xa6c4, 0xaaef,
        0x92e0, 0xd2e3, 0xc960, 0xd557, 0xd4a0, 0xda50, 0x5d55, 0x56a0,
        0xa6d0, 0x55d4, 0x52d0, 0xa9b8, 0xa950, 0xb4a0, 0xb6a6, 0xad50,
        0x55a0, 0xaba4, 0xa5b0, 0x52b0, 0xb273, 0x6930, 0x7337, 0x6aa0,
        0xad50, 0x4b55, 0x4b6f, 0xa570, 0x54e4, 0xd260, 0xe968, 0xd520,
        0xdaa0, 0x6aa6, 0x56df, 0x4ae0, 0xa9d4, 0xa4d0, 0xd150, 0xf252,
        0xd520
};

static const int solarTermInfo[] = {
         0,  21208,  42467,  63836,  85337, 107014, 128867, 150921,
    173149, 195551, 218072, 240693, 263343, 285989, 308563, 331033,
    353350, 375494, 397447, 419210, 440795, 462224, 483532, 504758
};

static const char* lunarString1[] = {
    "零", "一", "二", "三", "四", "五", "六", "七", "八", "九"
};

static const char* lunarString2[] = {
     "初", "十", "廿", "正", "冬", "腊", "闰"
};

static const char* animalsString[] = {
      "鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪"
};

static const char* tianganString[]{
      "甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"
};

static const char* dizhiString[]{
      "子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"
};

static const char* solarTermString[]{
    "小寒", "大寒", "立春", "雨水", "惊蛰", "春分",
    "清明", "谷雨", "立夏", "小满", "芒种", "夏至",
    "小暑", "大暑", "立秋", "处暑", "白露", "秋分",
    "寒露", "霜降", "立冬", "小雪", "大雪", "冬至"
};



//内部函数
/**
* 返回农历年闰月月份
* @param lunarYear 指定农历年份(数字)
* @return 该农历年闰月的月份(数字,没闰返回0)
*/
static int getLunarLeapMonth(int lunarYear) {
    // 数据表中,每个农历年用16bit来表示,
    // 前12bit分别表示12个月份的大小月,最后4bit表示闰月
    // 若4bit全为1或全为0,表示没闰, 否则4bit的值为闰月月份
    int leapMonth = lunarInfo[lunarYear - 1900] & 0xf;
    leapMonth = (leapMonth == 0xf ? 0 : leapMonth);
    return leapMonth;
}

/**
* 返回农历年正常月份的总天数
* @param lunarYear 指定农历年份(数字)
* @param lunarMonth 指定农历月份(数字)
* @return 该农历年闰月的月份(数字,没闰返回0)
*/
static int getLunarMonthDays(int lunarYear, int lunarMonth) {
    // 数据表中,每个农历年用16bit来表示,
    // 前12bit分别表示12个月份的大小月,最后4bit表示闰月
    int daysInLunarMonth = ((lunarInfo[lunarYear - 1900] & (0x10000 >> lunarMonth)) != 0) ? 30 : 29;
    return daysInLunarMonth;
}

/**
* 返回农历年闰月的天数
* @param lunarYear 指定农历年份(数字)
* @return 该农历年闰月的天数(数字)
*/
static int getLunarLeapDays(int lunarYear) {
    // 下一年最后4bit为1111,返回30(大月)
    // 下一年最后4bit不为1111,返回29(小月)
    // 若该年没有闰月,返回0
    return getLunarLeapMonth(lunarYear) > 0 ? ((lunarInfo[lunarYear - 1899] & 0xf) == 0xf ? 30 : 29) : 0;
}

/**
 * 返回农历年的总天数
 * @param lunarYear 指定农历年份(数字)
 * @return 该农历年的总天数(数字)
 */
static int getLunarYearDays(int lunarYear) {
    // 按小月计算,农历年最少有12 * 29 = 348天
    int daysInLunarYear = 348;
    // 数据表中,每个农历年用16bit来表示,
    // 前12bit分别表示12个月份的大小月,最后4bit表示闰月
    // 每个大月累加一天
    for (int i = 0x8000; i > 0x8; i >>= 1) {
        daysInLunarYear += ((lunarInfo[lunarYear - 1900] & i) != 0) ? 1 : 0;
    }
    // 加上闰月天数
    daysInLunarYear += getLunarLeapDays(lunarYear);

    return daysInLunarYear;
}

/**
 * 获得地支
 * @param cyclicalNumber
 * @return 地支 (数字)
 */
static int getDizhi(int cyclicalNumber) {
    return cyclicalNumber % 12;
}

/**
 * 获得天干
 * @param cyclicalNumber
 * @return 天干 (数字)
 */
static int getTiangan(int cyclicalNumber) {
    return cyclicalNumber % 10;
}

/**
 * 返回此月大小月信息
 * @param lunarYear, lunarMonth
 * @return 大月为 true，小月为 false
 */
static bool isMajorMonth(int lunarYear, int lunarMonth) {
    return getLunarMonthDays(lunarYear, lunarMonth) == 30;
}

/**
 * 干支字符串
 * @param cyclicalNumber 指定干支位置(数字,0为甲子)
 * @return 干支字符串
 */
static const char* getCyclicalString(int cyclicalNumber) {
    std::stringstream ss;
    ss << tianganString[getTiangan(cyclicalNumber)] << dizhiString[getDizhi(cyclicalNumber)];
    return ss.str().c_str();
}

/**
 * 返回指定数字的农历年份表示字符串
 * @param lunarYear 农历年份(数字,0为甲子)
 * @return 农历年份字符串
 */
static const char* getLunarYearString(int lunarYear) {
    return getCyclicalString(lunarYear - 1900 + 36);
}

/**
 * 返回指定数字的农历月份表示字符串
 * @param lunarMonth 农历月份(数字)
 * @return 农历月份字符串 (例:正)
 */
static const char* getLunarMonthString(int lunarMonth) {
    static const char* lunarMonthString = {};
    if (lunarMonth == 1) {
        lunarMonthString = lunarString2[3];
    }
    else if (lunarMonth == 10) {
        lunarMonthString = lunarString2[1];
    }
    else if (lunarMonth > 10) {
        lunarMonthString = lunarString2[lunarMonth % 10 + 3];
    }
    else if (lunarMonth % 10 > 0) {
        lunarMonthString = lunarString1[lunarMonth % 10];
    }
    static std::string lunarMonthStringReturn;
    lunarMonthStringReturn = lunarMonthString;
    return lunarMonthStringReturn.c_str();
}

/**
 * 返回指定数字的农历日表示字符串
 * @param lunarDay 农历日(数字)
 * @return 农历日字符串 (例: 廿一)
 */
static const char* getLunarDayString(int lunarDay) {
    if (lunarDay < 1 || lunarDay>30) return "";
    int i1 = lunarDay / 10;
    int i2 = lunarDay % 10;
    const char* lunarDayString1 = lunarString2[i1];
    const char* lunarDayString2 = lunarString1[i2];
    if (lunarDay < 11) {
        lunarDayString1 = lunarString2[0];
        if (i2 == 0) lunarDayString2 = lunarString2[1];
    }
    else if (i2 == 0) {
        lunarDayString2 = lunarString2[1];
        lunarDayString1 = lunarString1[i1];
    }
    static std::string lunarDayStringReturn;
    lunarDayStringReturn = lunarDayString1;
    lunarDayStringReturn += lunarDayString2;
    return lunarDayStringReturn.c_str();
}

/**
 * 返回公历年节气的日期
 * @param solarYear 指定公历年份(数字)
 * @param index 指定节气序号(数字,0从小寒算起)
 * @return 日期(数字,所在月份的第几天)
 */
static int getSolarTermDay(int solarYear, int index) {
    // 使用 long long 避免溢出
    long long baseTime = 2208549300000LL;  // 1900-01-06 02:05:00 （毫秒）
    double yearOffset = 31556925974.7 * (solarYear - 1900);  // 精确计算
    long long indexOffset = solarTermInfo[index] * 60000LL;  // 转换为毫秒

    // 计算节气 UTC 时间（毫秒）
    long long ll = yearOffset + indexOffset - baseTime;

    // 转换为秒
    time_t seconds = ll / 1000;

    // 计算 UTC 时间
    struct tm timeinfo;
    gmtime_s(&timeinfo, &seconds);

    return timeinfo.tm_mday;
}

/**
 * 返回全球标准时间 (UTC) (或 GMT) 的 1970 年 1 月 2 日到所指定日期之间所间隔的秒数。
 * @param y 指定年份
 * @param m 指定月份
 * @param d 指定日期
 * @param h 指定小时
 * @param min 指定分钟
 * @param sec 指定秒数
 * @return 全球标准时间 (UTC) (或 GMT) 的 1970 年 1 月 2 日到所指定日期之间所间隔的秒数
 */
static long UTC(int y, int m, int d, int h, int min, int sec) {
    struct tm input = { 0 };
    input.tm_year = y - 1900;
    input.tm_mon = m - 1;
    input.tm_mday = d;
    input.tm_hour = h;
    input.tm_min = min;
    input.tm_sec = sec;

    // 设置 1970-1-2
    static struct tm base = { 0 };
    base.tm_year = 1970 - 1900;   // 1970 年
    base.tm_mon = 0;             // 1 月（从 0 开始）
    base.tm_mday = 2;

    // 计算时间戳
    time_t input_time = mktime(&input);
    time_t base_time = mktime(&base);

    // 计算天数差，转换为 long
    long offset = (long)(difftime(input_time, base_time));

    return offset;
}

/**
 * 计算农历和节气
 */
static void lunarCalculate() {
    // 计算当前与1970年1月2日的天数差再加上1970年1月2日与1900年1月31日的天数差，转换为 long
    long offset = UTC(solarYear, solarMonth + 1, solarDay, 0, 0, 0) / 86400 + 25538;

    // 农历年数字
    lunarYear = 1900;
    int daysInLunarYear = getLunarYearDays(lunarYear);
    while (lunarYear < 2100 && offset >= daysInLunarYear) {
        offset -= daysInLunarYear;
        daysInLunarYear = getLunarYearDays(++lunarYear);
    }
    // 按农历月递减每月的农历天数，确定农历月份
    lunarMonth = 1;
    // 所在农历年闰哪个月,若没有返回0
    int leapMonth = getLunarLeapMonth(lunarYear);
    // 是否闰年
    bool isLeapYear = leapMonth > 0;
    // 闰月是否递减
    bool leapDec = false;
    bool isLeapMonth = false;
    int daysInLunarMonth = 0;
    while (lunarMonth < 13 && offset>0) {
        if (isLeapMonth && leapDec) { // 如果是闰年,并且是闰月
            // 所在农历年闰月的天数
            daysInLunarMonth = getLunarLeapDays(lunarYear);
            leapDec = false;
        }
        else {
            // 所在农历年指定月的天数
            daysInLunarMonth = getLunarMonthDays(lunarYear, lunarMonth);
        }
        if (offset < daysInLunarMonth) {
            break;
        }
        offset -= daysInLunarMonth;

        if (leapMonth == lunarMonth && isLeapMonth == false) {
            // 下个月是闰月
            leapDec = true;
            isLeapMonth = true;
        }
        else {
            // 月份递增
            lunarMonth++;
        }
    }
    // 农历月数字
    lunarMonth = lunarMonth;
    // 是否闰月
    isLeapMonth = (lunarMonth == leapMonth && isLeapMonth);
    // 农历日数字
    lunarDay = (int)offset + 1;
    // 取得干支历


    /**
      * 取干支历 不是历年，历月干支，而是中国的从立春节气开始的节月，是中国的太阳十二宫，阳历的。
     */

     // 干支年1900年立春后为庚子年(60进制36)
    int term2 = getSolarTermDay(solarYear, 2); // 立春日期
    // 依节气调整二月分的年柱, 以立春为界
    if (solarMonth < 1 || (solarMonth == 1 && solarDay < term2)) {
        cyclicalYear = (solarYear - 1900 + 36 - 1) % 60;
    }
    else {
        cyclicalYear = (solarYear - 1900 + 36) % 60;
    }

    // 干支月 1900年1月小寒以前为 丙子月(60进制12)
    int firstNode = getSolarTermDay(solarYear, solarMonth * 2); // 传回当月「节」为几日开始
    // 依节气月柱, 以「节」为界
    if (solarDay <= firstNode) {
        cyclicalMonth = ((solarYear - 1900) * 12 + solarMonth + 12) % 60;
    }
    else {
        cyclicalMonth = ((solarYear - 1900) * 12 + solarMonth + 13) % 60;
    }

    // 当月一日与 1900/1/1 相差天数
    // 1900/1/1与 1970/1/2 相差25568日, 1900/1/1 日柱为甲戌日(60进制10)
    cyclicalDay = (int)(UTC(solarYear, solarMonth + 1, solarDay, 0, 0, 0) / 86400 + 25568 + 10) % 60;
}



//导出函数
/**
 * 农历月是否是闰月
 * @return 农历月是否是闰月
 */
extern "C" __declspec(dllexport) bool IsLeapMonth() {
    return isLeapMonth;
}

/**
 * 农历年是否是闰年
 * @return 农历年是否是闰年
 */
extern "C" __declspec(dllexport) bool IsLeapYear() {
    return isLeapYear;
}


/**
 * 公历日期
 * @return 公历日期
 */
extern "C" __declspec(dllexport) int GetSolarDay() {
    return solarDay;
}

/**
 * 公历月份
 * @return 公历月份 (不是从0算起)
 */
extern "C" __declspec(dllexport) int GetSolarMonth() {
    return solarMonth + 1;
}

/**
 * 公历年份
 * @return 公历年份
 */
extern "C" __declspec(dllexport) int GetSolarYear() {
    return solarYear;
}

/**
 * 农历日期
 * @return 农历日期
 */
extern "C" __declspec(dllexport) int GetLunarDay() {
    return lunarDay;
}

/**
 * 农历月份
 * @return 农历月份
 */
extern "C" __declspec(dllexport) int GetLunarMonth() {
    return lunarMonth;
}

/**
 * 农历年份
 * @return 农历年份
 */
extern "C" __declspec(dllexport) int GetLunarYear() {
    return lunarYear;
}

/**
 * 年份天干
 * @return 年份天干
 */
extern "C" __declspec(dllexport) int GetTianganYear() {
    return getTiangan(cyclicalYear);
}

/**
 * 月份天干
 * @return 月份天干
 */
extern "C" __declspec(dllexport) int GetTianganMonth() {
    return getTiangan(cyclicalMonth);
}

/**
 * 日期天干
 * @return 日期天干
 */
extern "C" __declspec(dllexport) int GetTianganDay() {
    return getTiangan(cyclicalDay);
}

/**
 * 年份地支
 * @return 年分地支
 */
extern "C" __declspec(dllexport) int GetDizhiYear() {
    return getDizhi(cyclicalYear);
}

/**
 * 月份地支
 * @return 月份地支
 */
extern "C" __declspec(dllexport) int GetDizhiMonth() {
    return getDizhi(cyclicalMonth);
}

/**
 * 日期地支
 * @return 日期地支
 */
extern "C" __declspec(dllexport) int GetDizhiDay() {
    return getDizhi(cyclicalDay);
}

/**
 * 返回农历年字符串
 * @return 农历年字符串
 */
extern "C" __declspec(dllexport) const char* GetLunarYearString() {
    static std::string lunarYearReturn;
    lunarYearReturn = getLunarYearString(lunarYear);
    return lunarYearReturn.c_str();
}

/**
 * 返回农历月字符串
 * @return 农历月字符串
 */
extern "C" __declspec(dllexport) const char* GetLunarMonthString() {
    static std::string lunarMonthReturn;
    lunarMonthReturn = (isLeapMonth ? lunarString2[6] : "");
    lunarMonthReturn += getLunarMonthString(lunarMonth);
    return lunarMonthReturn.c_str();
}

/**
 * 返回农历日字符串
 * @return 农历日字符串
 */
extern "C" __declspec(dllexport) const char* GetLunarDayString() {
    static std::string lunarDayReturn;
    lunarDayReturn = getLunarDayString(lunarDay);
    return lunarDayReturn.c_str();
}

/**
 * 取农历年生肖
 * @return 农历年生肖(例:龙)
 */
extern "C" __declspec(dllexport) const char* GetAnimalString() {
    static std::string animalsStringReturn;
    animalsStringReturn = animalsString[(lunarYear - 4) % 12];
    return animalsStringReturn.c_str();
}

/**
 * 取得干支年字符串
 * @return 干支年字符串
 */
extern "C" __declspec(dllexport) const char* GetCyclicaYear() {
    static std::string cyclicalYearReturn;
    cyclicalYearReturn = getCyclicalString(cyclicalYear);
    return cyclicalYearReturn.c_str();
}

/**
 * 取得干支月字符串
 * @return 干支月字符串
 */
extern "C" __declspec(dllexport) const char* GetCyclicaMonth() {
    static std::string cyclicalMonthReturn;
    cyclicalMonthReturn = getCyclicalString(cyclicalMonth);
    return cyclicalMonthReturn.c_str();
}

/**
 * 取得干支日字符串
 * @return 干支日字符串
 */
extern "C" __declspec(dllexport) const char* GetCyclicaDay() {
    static std::string cyclicalDayReturn;
    cyclicalDayReturn = getCyclicalString(cyclicalDay);
    return cyclicalDayReturn.c_str();
}

/**
 * 返回公历日期的节气字符串
 * @return 二十四节气字符串,若不是节气日,返回空串(例:冬至)
 */
extern "C" __declspec(dllexport) const char* GetTermString() {
    // 二十四节气
    static const char* termString = "";
    if (getSolarTermDay(solarYear, solarMonth * 2) == solarDay) {
        termString = solarTermString[solarMonth * 2];
    }
    else if (getSolarTermDay(solarYear, solarMonth * 2 + 1) == solarDay) {
        termString = solarTermString[solarMonth * 2 + 1];
    }
    static std::string termStringReturn;
    termStringReturn = termString;
    return termStringReturn.c_str();
}

/**
 * 初始化当前日期
 */
extern "C" __declspec(dllexport) void InitTimeNow() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    solarYear = st.wYear;
    solarMonth = st.wMonth - 1;
    solarDay = st.wDay;
    lunarCalculate();
}

/**
 * 初始化指定日期
 * @param year 指定年份
 * @param month 指定月份
 * @param day 指定日期
 */
extern "C" __declspec(dllexport) void InitTimeSet(int year, int month, int day) {
    solarYear = year;
    solarMonth = month - 1;
    solarDay = day;
    lunarCalculate();
}

/**
 * 返回格式化后的日期字符串
 * @param format 格式化字符串，例如 "YY年MM月DD日 yy mm dd TT"
 * 支持的占位符包括：
 * - YY：干支年份（例如：甲子）
 * - MM：干支月份（例如：庚子）
 * - DD：干支日（例如：戊戌）
 * - yy：生肖（例如：鼠）
 * - mm：农历月份（例如：正、腊、二）
 * - dd：农历日（例如：初一）
 * - TT：节气（例如：立春）
 * @return 格式化后的日期字符串，调用者需要负责释放返回的内存（使用 free() 函数）
 */
extern "C" __declspec(dllexport) const char* GetFormattedString(const char* format) {
    std::string formattedString = format; // 将输入的格式化字符串复制到 std::string 对象中
    size_t pos; // 用于存储占位符在字符串中的位置

    // 替换 YY (农历年份)
    pos = formattedString.find("YY");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetCyclicaYear()); // 调用 GetCyclicaYear() 函数获取农历年份，并替换占位符
    }

    // 替换 MM (农历月份)
    pos = formattedString.find("MM");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetCyclicaMonth()); // 调用 GetCyclicaMonth() 函数获取农历月份，并替换占位符
    }

    // 替换 DD (农历日)
    pos = formattedString.find("DD");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetCyclicaDay()); // 调用 GetCyclicaDay() 函数获取农历日，并替换占位符
    }

    // 替换 yy (生肖)
    pos = formattedString.find("yy");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetAnimalString()); // 调用 GetAnimalString() 函数获取生肖，并替换占位符
    }

    // 替换 mm (农历月份的中文表示)
    pos = formattedString.find("mm");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetLunarMonthString()); // 调用 GetLunarMonthString() 函数获取农历月份的中文表示，并替换占位符
    }

    // 替换 dd (农历日的中文表示)
    pos = formattedString.find("dd");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetLunarDayString()); // 调用 GetLunarDayString() 函数获取农历日的中文表示，并替换占位符
    }

    // 替换 TT (农历节气)
    pos = formattedString.find("TT");
    if (pos != std::string::npos) {
        formattedString.replace(pos, 2, GetTermString()); // 调用 GetTermString() 函数获取农历节气，并替换占位符
    }

    static std::string formattedStringReturn;
    formattedStringReturn = formattedString;
    return formattedStringReturn.c_str();
}

static BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

