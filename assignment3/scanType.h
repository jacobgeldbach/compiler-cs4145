#ifndef SCANTYPE_H
#define SCANTYPE_H
typedef struct token_data_s {
    int token_class;  /* Token class */
    int line_num;     /* Line that this token occured on */
    char *token_str;  /* The actual string that was read */
    int nvalue;	     /* Any numeric value or boolean value */
    char cvalue;     /* Any character value */
    char *svalue;    /* Any string value */
} token_data_t;

#endif
