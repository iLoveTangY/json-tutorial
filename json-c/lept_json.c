/*
 * Created by tang on 18-10-24.
 * */
#include "lept_json.h"
#include <stdlib.h> /* NULL */
#include <assert.h> /* assert() */

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

/* 减少解析函数之间传递参数的个数，将一些参数放入这个结构体 */
typedef struct
{
    const char* json;
} lept_context;

/* @desc: 跳过json字符串中的空格
 * @param c: 存放有json字符串
 * */
static void lept_parse_whitespace(lept_context* c)
{
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p; /* 直接更新到非空白字符 */
}

/* @desc: 解析"null"
 * @param c: json字符串存放在其中
 * @param v: 解析结果
 * */
static int lept_parse_null(lept_context* c, lept_value* v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

static int lept_parse_true(lept_context* c, lept_value* v)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

static int lept_parse_false(lept_context* c, lept_value* v)
{
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

/* @desc: 解析json"值"
 * */
static int lept_parse_value(lept_context* c, lept_value* v)
{
    switch (*c->json)
    {
        case 'n':
            return lept_parse_null(c, v);
        case 't':
            return lept_parse_true(c, v);
        case 'f':
            return lept_parse_false(c, v);
        case '\0':
            return LEPT_PARSE_EXPECT_VALUE;
        default:
            return LEPT_PARSE_INVALID_VALUE;
    }
}

/* @desc: 解析json字符串
 * @param v: 解析结果
 * @param json: 需要解析的字符串
 * */
int lept_parse(lept_value* v, const char* json)
{
    lept_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;    /* 如果解析失败，会将v设为null类型，在此先将其设为null类型 */
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK)
    {
        lept_parse_whitespace(&c);
        if (*c.json != '\0')    /* 如果值之后，空白之后还有其它字符 */
        {
            v->type = LEPT_NULL;
            return LEPT_PARSE_ROOT_NOT_SIGULAR;
        }
    }
    return ret;
}

lept_type lept_get_type(const lept_value* v)
{
    assert(v != NULL);
    return v->type;
}
