#ifndef _NL_TYPES_H
#define _NL_TYPES_H

typedef enum {
  CODESET,
  D_T_FMT,
  D_FMT,
  T_FMT,
  T_FMT_AMPM,
  AM_STR,
  PM_STR,
  DAY_1, DAY_2, DAY_3, DAY_4, DAY_5, DAY_6, DAY_7,
  ABDAY_1, ABDAY_2, ABDAY_3, ABDAY_4, ABDAY_5, ABDAY_6, ABDAY_7,
  MON_1, MON_2, MON_3, MON_4, MON_5, MON_6,
  MON_7, MON_8, MON_9, MON_10, MON_11, MON_12,
  ABMON_1, ABMON_2, ABMON_3, ABMON_4, ABMON_5, ABMON_6,
  ABMON_7, ABMON_8, ABMON_9, ABMON_10, ABMON_11, ABMON_12,
  ERA,
  ERA_D_FMT,
  ERA_D_T_FMT,
  ERA_T_FMT,
  ALT_DIGITS,
  RADIXCHAR,
  THOUSEP,
  YESEXPR,
  NOEXPR,
  CRNCYSTR
} nl_item;

typedef void* nl_catd;

enum { NL_SETD=0, NL_CAT_LOCALE=1 };

#endif
