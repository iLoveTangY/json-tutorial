/*
 * Ceated by tang
 * */
#ifndef LEPTJSON_TEST_LEPT_JSON_H
#define LEPTJSON_TEST_LEPT_JSON_H

#include <stddef.h>
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
typedef struct lept_value lept_value;
typedef struct lept_member lept_member;

struct lept_value
{
    union
    {
        struct
        {
            lept_member* m; /* lept_member的数组 */
            size_t size;    /* 数组大小 */
        }o;  /* object */
        struct
        {
            lept_value* e;
            size_t size;    /* 元素个数，不是字节单位 */
        }a; /* array */
        struct
        {
            char* s;
            size_t len;
        }s /* string */;
    }u;
    double n;
    lept_type type;
};

struct lept_member
{
    char* k;        /* json 对象的键，只能为字符串 */
    size_t klen;    /* 键的长度 */
    lept_value v;   /* 值，可以是任何合法的json类型，包括object类型 */
};

/* 解析函数的返回值，表示各种状态 */
enum
{
    LEPT_PARSE_OK = 0,          /* 成功解析 */
    LEPT_PARSE_EXPECT_VALUE,    /* 需要一个value但是没有（只有空白） */
    LEPT_PARSE_INVALID_VALUE,   /* 无效的value */
    LEPT_PARSE_ROOT_NOT_SINGULAR, /* 一个值之后还有其他无效字符 */
    LEPT_PARSE_NUMBER_TOO_BIG,
    LEPT_PARSE_MISS_QUOTATION_MARK,
    LEPT_PARSE_INVALID_STRING_ESCAPE,
    LEPT_PARSE_INVALID_STRING_CHAR,
    LEPT_PARSE_INVALID_UNICODE_HEX,
    LEPT_PARSE_INVALID_UNICODE_SURROGATE,
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
    LEPT_PARSE_MISS_KEY,
    LEPT_PARSE_MISS_COLON,
    LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET
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

#endif /* LEPTJSON_TEST_LEPT_JSON_H */

void lept_free(lept_value* v);
#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

#define lept_set_null(v) lept_free(v)

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);
