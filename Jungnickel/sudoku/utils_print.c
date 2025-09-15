#include "sudoku.h"

void print_mask_binary(sudoku_mask mask, const char *label)
{
	int i;

	if (label)
		printf("%s: ", label);
	printf("0b");
	for (i = 8; i >= 0; i--)
	{
		if (CHECK_BIT(mask, i))
			printf("1");
		else
			printf("0");
	}
	printf(" (0x%03X)", mask);
	nl(1);
}

void print_mask_candidates(sudoku_mask mask, const char *label)
{
	int num;
	int first;

	if (label)
		printf("%s", label);
	printf("[");
	first = 1;
	for (num = 1; num <= SUDOKU_SIZE; num++)
	{
		if (CHECK_BIT(mask, NUM_TO_BIT(num)))
		{
			if (!first)
				printf(",");
			printf("%d", num);
			first = 0;
		}
	}
	if (first)
		printf("none");
	printf("] (%d candidates)", COUNT_BITS(mask));
}

void print_masks_status(t_sudoku_masks *masks)
{
    int i;

    printf("=== Masks Status ===\n");

    printf("Row masks:\n");
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        printf("  Row %d: ", i);
        print_mask_binary(masks->row_masks[i], NULL);
    }

    printf("Column masks:\n");
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        printf("  Col %d: ", i);
        print_mask_binary(masks->col_masks[i], NULL);
    }

    printf("Box masks:\n");
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        printf("  Box %d: ", i);
        print_mask_binary(masks->box_masks[i], NULL);
    }
}

void print_masks_candidates(t_sudoku_masks *masks)
{
    int i;

    printf("=== Used Numbers ===\n");

    printf("Row constraints:\n");
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        printf("  Row %d: ", i);
        print_mask_candidates(masks->row_masks[i], "");
        nl(1);
    }

    printf("Column constraints:\n");
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        printf("  Col %d: ", i);
        print_mask_candidates(masks->col_masks[i], "");
        nl(1);
    }

    printf("Box constraints:\n");
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        printf("  Box %d: ", i);
        print_mask_candidates(masks->box_masks[i], "");
        nl(1);
    }
}
