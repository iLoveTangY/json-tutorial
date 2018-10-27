/*
 * Ceated by tang
 * */
#ifndef LEPTJSON_TEST_LEPT_JSON_H
#define LEPTJSON_TEST_LEPT_JSON_H

/* json 的所有数据类型，共 7 种 */
typedef enum
{
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

/* 自定义类型，存储解析结果 */
typedef struct
{
    double n;
    lept_type type;
} lept_value;

/* 解析函数的返回值，表示各种状态 */
enum
{
    LEPT_PARSE_OK = 0,          /* 成功解析 */
    LEPT_PARSE_EXPECT_VALUE,    /* 需要一个value但是没有（只有空白） */
    LEPT_PARSE_INVALID_VALUE,   /* 无效的value */
    LEPT_PARSE_ROOT_NOT_SINGULAR, /* 一个值之后还有其他无效字符 */
    LEPT_PARSE_NUMBER_TOO_BIG
};

/* @desc:       解析指定的json字符串
 * @param v:    解析结果
 * @param json: 要解析的字符串，不应该修改它，因此为 const
 * @return:     自定义枚举类型，表示解析函数执行完之后的状态
 * */
int lept_parse(lept_value* v, const char* json);

/* @desc:    获取制定解析结果的类型
 * @param v: 要获取类型的lept_value
 * @return:  枚举值，得到的type
 * */
lept_type lept_get_type(const lept_value* v);

/* @desc:   获取数字类型的值
 * @return: 数字值
 * */
double lept_get_number(const lept_value* v);

#endif /* LEPTJSON_TEST_LEPT_JSON_H */
