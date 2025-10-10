#!/usr/bin/python3
import sys


def solve_nqueens(N):
    """
    Find all possible solutions to the N-Queens problem

    Args:
        N (int): Size of the chessboard and number of queens
    """
    def is_safe(board, row, col):
        """
        Check if a queen can be placed on board[row][col]

        Args:
            board (list): Current board state
            row (int): Row to check
            col (int): Column to check

        Returns:
            bool: True if safe to place a queen, False otherwise
        """
        # Check this row on left side
        for i in range(col):
            if board[row][i] == 1:
                return False

        # Check upper diagonal on left side
        for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
            if board[i][j] == 1:
                return False

        # Check lower diagonal on left side
        for i, j in zip(range(row, N, 1), range(col, -1, -1)):
            if board[i][j] == 1:
                return False

        return True

    def solve(board, col, solutions):
        """
        Recursive backtracking function to solve N-Queens

        Args:
            board (list): Current board state
            col (int): Current column being processed
            solutions (list): List to store valid solutions

        Returns:
            bool: True if solution found, False otherwise
        """
        # Base case: all queens are placed
        if col >= N:
            # Convert board to solution format
            solution = []
            for i in range(N):
                for j in range(N):
                    if board[i][j] == 1:
                        solution.append([i, j])
            solutions.append(solution)
            return True

        # Consider this column and try placing this queen in all rows
        res = False
        for row in range(N):
            # Check if queen can be placed on board[row][col]
            if is_safe(board, row, col):
                # Place this queen in board[row][col]
                board[row][col] = 1

                # Recur to place rest of the queens
                res = solve(board, col + 1, solutions) or res

                # If placing queen doesn't lead to a solution,
                # then remove queen from board[row][col]
                board[row][col] = 0

        return res

    # Validate N
    try:
        N = int(N)
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if N < 4:
        print("N must be at least 4")
        sys.exit(1)

    # Initialize board
    board = [[0 for _ in range(N)] for _ in range(N)]
    solutions = []

    # Solve N-Queens problem
    solve(board, 0, solutions)

    # Print solutions
    for solution in solutions:
        print(solution)


# Main execution
if __name__ == "__main__":
    # Check argument count
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    # Solve N-Queens
    solve_nqueens(sys.argv[1])
