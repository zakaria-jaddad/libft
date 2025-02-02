#include "../include/test.h"
#include "../include/util.h"
#include <stdio.h>

typedef struct test
{
  char *desc;
  const char *src;
  char *dst;
  const char *memmove_src;
  char *memmove_dst;
  size_t n;
  void *expected_output;
} ft_memmove_test;

static int run_no_overlap_tests(ft_memmove_test *tests)
{
  int error = 0;
  while (tests->desc)
  {
    ft_memmove(tests->dst, tests->src, tests->n);
    if (memcmp(tests->memmove_dst, tests->dst, tests->n))
    {
      printf(" " RED " %s Expected ", tests->desc);
      print_byte_red(tests->memmove_dst, tests->n);
      printf("output ");
      print_byte_red(tests->dst, tests->n);
      printf("\n");
      error++;
    }
    else
    {
      printf(" " GREEN CHECKMARK " %s Expected ", tests->desc);
      print_byte_green(tests->memmove_dst, tests->n);
      printf("output ");
      print_byte_green(tests->dst, tests->n);
      printf("\n");
    }
    tests++;
  }
  return error;
}

static int run_overlap_tests(ft_memmove_test *tests)
{
  int error = 0;
  while (tests->desc)
  {
    ft_memmove(tests->dst + 2, tests->dst, tests->n);
    if (memcmp(tests->memmove_dst, tests->dst, tests->n))
    {
      printf(" " RED " %s Expected ", tests->desc);
      print_byte_red(tests->memmove_dst, tests->n);
      printf("output ");
      print_byte_red(tests->dst, tests->n);
      printf("\n");
      error++;
    }
    else
    {
      printf(" " GREEN CHECKMARK " %s Expected ", tests->desc);
      print_byte_green(tests->memmove_dst, tests->n);
      printf("output ");
      print_byte_green(tests->dst, tests->n);
      printf("\n");
    }
    tests++;
  }
  return error;
}

/* void *ft_memmove(void *dst, const void *src, size_t len) */
int ft_memmove_tests(void)
{
  char src[10][100] = {
      "abce\xff",
      {0, 0, 0, 0},
      "hello, World",
      {255, 'b', 3, 0, 'A', 30, 128},
  };
  char dst[10][100] = {};

  char memmove_src[10][100] = {
      "abce\xff",
      {0, 0, 0, 0},
      "hello, World",
      {255, 'b', 3, 0, 'A', 30, 128},
  };
  char memmove_dst[10][100] = {};

  ft_memmove_test tests_no_overlap[] = {
      {
          .desc = "ft_memmove(\"abce\xff\", \"\", 10)",
          .src = src[0],
          .dst = dst[0],
          .n = 10,
          .memmove_src = memmove_src[0],
          .memmove_dst = memmove_dst[0],
          .expected_output = memmove(memmove_dst[0], memmove_src[0], 10),
      },
      {
          .desc = "ft_memmove({0, 0, 0, 0}, {0, 0, 0, 0}, 4)",
          .src = src[1],
          .dst = dst[1],
          .memmove_src = memmove_src[1],
          .memmove_dst = memmove_dst[1],
          .n = 4,
          .expected_output = memmove(memmove_dst[1], memmove_src[1], 4),
      },
      {
          .desc = 0,
      },
  };

  ft_memmove_test tests_overlap[] = {
      {
          .desc = "ft_memmove(\"hello, World\" + 2, \"hello, World\", 12)",
          .src = src[2],
          .dst = src[2],
          .memmove_src = memmove_src[2],
          .memmove_dst = memmove_src[2],
          .n = 12,
          .expected_output = memmove(memmove_src[2] + 2, memmove_src[2], 12),
      },
      {
          .desc = "ft_memmove({3, 0, 'A', 30, 128}, {255, 'b', 3, 0, 'A', 30, "
                  "128}, 8)",
          .src = src[3],
          .dst = src[3],
          .memmove_src = memmove_src[3],
          .memmove_dst = memmove_src[3],
          .n = 8,
          .expected_output = memmove(memmove_src[3] + 2, memmove_src[3], 8),

      },
      {
          .desc = 0,
      },
  };
  return run_no_overlap_tests(tests_no_overlap) +
         run_overlap_tests(tests_overlap);
}
