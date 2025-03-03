此 C++ DLL 的主要功能是根据公历日期计算相应的农历日期、节气以及干支纪年等信息。它提供了一系列导出函数，方便其他程序调用，获取所需的日期信息。
DLL 功能概述：

 * 公历转农历： 将公历日期（年、月、日）转换为对应的农历日期。
 * 节气计算： 根据公历日期，判断该日期是否为二十四节气中的某一个，并返回节气名称。
 * 干支纪年： 计算公历日期对应的干支纪年、纪月和纪日。
 * 生肖计算： 根据农历年份，计算对应的生肖。
 * 日期信息查询： 提供一系列函数，用于查询公历和农历的年、月、日，以及是否闰月、闰年等信息。
 * 日期字符串生成： 提供函数，用于生成农历年、月、日的字符串表示形式。
导出函数功能和用法
以下是 DLL 提供的导出函数及其功能和用法：
1. 初始化日期
 * void InitTimeNow()：
   * 功能：使用当前系统时间初始化日期。
   * 用法：调用此函数后，可以使用其他 Get... 函数获取当前日期的农历、节气和干支信息。
 * void InitTimeSet(int year, int month, int day)：
   * 功能：使用指定的公历日期初始化日期。
   * 参数：
     * year：公历年份。
     * month：公历月份（1-12）。
     * day：公历日期。
   * 用法：调用此函数后，可以使用其他 Get... 函数获取指定日期的农历、节气和干支信息。
2. 获取公历日期
 * int GetSolarDay()：
   * 功能：返回公历日期。
   * 返回值：公历日期。
 * int GetSolarMonth()：
   * 功能：返回公历月份。
   * 返回值：公历月份（1-12）。
 * int GetSolarYear()：
   * 功能：返回公历年份。
   * 返回值：公历年份。
3. 获取农历日期
 * int GetLunarDay()：
   * 功能：返回农历日期。
   * 返回值：农历日期。
 * int GetLunarMonth()：
   * 功能：返回农历月份。
   * 返回值：农历月份。
 * int GetLunarYear()：
   * 功能：返回农历年份。
   * 返回值：农历年份。
 * char* GetLunarYearString()：
   * 功能：返回农历年字符串
   * 返回值：农历年字符串，例如：“甲子”。
 * char* GetLunarMonthString()：
   * 功能：返回农历月字符串
   * 返回值：农历月字符串，例如：“正月”，“闰五月”。
 * char* GetLunarDayString()：
   * 功能：返回农历日字符串
   * 返回值：农历日字符串，例如：“初一”，“十五”。
4. 获取干支信息
 * int GetTianganYear()、int GetTianganMonth()、int GetTianganDay()：
   * 功能：分别返回年份、月份和日期的天干。
   * 返回值：天干（0-9，分别对应“甲”到“癸”）。
 * int GetDizhiYear()、int GetDizhiMonth()、int GetDizhiDay()：
   * 功能：分别返回年份、月份和日期的地支。
   * 返回值：地支（0-11，分别对应“子”到“亥”）。
 * char* GetCyclicaYear()、char* GetCyclicaMonth()、char* GetCyclicaDay()：
   * 功能：分别返回干支年份、月份和日期的字符串。
   * 返回值：干支字符串，例如：“甲子”。
5. 获取其他信息
 * bool IsLeapMonth()：
   * 功能：判断农历月份是否为闰月。
   * 返回值：true 表示闰月，false 表示非闰月。
 * bool IsLeapYear()：
   * 功能：判断农历年份是否为闰年。
   * 返回值：true 表示闰年，false 表示非闰年。
 * char* GetAnimalString()：
   * 功能：返回农历年份对应的生肖。
   * 返回值：生肖字符串，例如：“龙”。
 * char* GetTermString()：
   * 功能：返回公历日期对应的节气。
   * 返回值：节气字符串，例如：“冬至”。如果不是节气日，则返回空字符串。
6. 用法示例
 * 初始化日期：
   * InitTimeNow()：获取当前日期的农历信息。
   * InitTimeSet(2023, 10, 26)：获取 2023 年 10 月 26 日的农历信息。
 * 获取农历日期：
   * GetLunarYearString()、GetLunarMonthString()、GetLunarDayString()：获取农历年、月、日的字符串。
 * 获取干支信息：
   * GetCyclicaYear()、GetCyclicaMonth()、GetCyclicaDay()：获取干支年、月、日的字符串。
 * 获取其他信息：
   * GetAnimalString()：获取生肖。
   * GetTermString()：获取节气。
   * IsLeapMonth()：判断是否闰月。
通过调用这些导出函数，你可以方便地在其他程序中使用该 DLL 提供的农历、节气和干支计算功能。