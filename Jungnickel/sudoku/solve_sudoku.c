#include "sudoku.h"

// static void test_basic_functions(int **board,  t_sudoku_masks *masks)
// {
//     printf("\n=== Basic Functions Test ===\n");
//     print_mask_binary(masks->row_masks[0], "Row 0 mask");
// 	nl(1);

//     printf("Testing can_place_number:\n");
//     for (int col = 0; col < SUDOKU_SIZE; col++)
//     {
//         if (board[0][col] == SUDOKU_EMPTY_CELL)
//         {
//             printf("  Cell (0,%d): ", col);
//             if (can_place_number(0, col, 1, masks))
//                 printf("Can place 1");
//             else
//                 printf("Cannot place 1");

//             if (can_place_number(0, col, 5, masks))
//                 printf(", Can place 5");
//             else
//                 printf(", Cannot place 5");
//             printf("\n");
//         }
//     }
// }
void solve_sudoku(int **board, int n)
{
    t_sudoku_masks masks;
    print_matrix_int(board, n, n);
    printf("Grid size: %d\n", n);
    init_masks(board, n, &masks);
	print_masks_status(&masks);
    // test_basic_functions(board, &masks);
    printf("%s\n",
            solve_backtracking(board, n, &masks) ?
            "successed" : "failed");
}
