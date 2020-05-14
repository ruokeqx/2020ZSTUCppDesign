#pragma once
//患者账号信息
#define PATIENT_FILE "patient.txt"	//文件格式：账户名	密码
//管理员信息
#define ADMIN_FILE "admin.txt"		//文件格式：姓名	身份证号码		手机号		密码
//普通门诊信息
#define COMMON_FILE "common.txt"	//文件格式：科室	上午最大预约量	周一——周日上午预约量(7个数据)	下午最大预约量	周一——周日下午与月亮(7个数据)
//专家门诊信息
#define EXPERT_FILE "expert.txt"	//文件格式：专家名	科室	日期(用数字表示)	上下午(用数字表示)	最大预约数量(maxNum)	当前可预约号(1-maxNum)
//电子挂号单
#define FORM_FILE "form.txt"		//文件格式：科室名称	患者姓名	就诊日期	上下午	就诊号	专家姓名