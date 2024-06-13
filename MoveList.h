#ifndef MOVELIST_H
#define MOVELIST_H
#include "Piece.h"
#include <iostream>

// MoveNode represents a single move in the doubly linked list
struct MoveNode {
    int startX, startY, endX, endY; // Coordinates of the move
    std::unique_ptr<Piece> capturedPiece; // Pointer to the piece that was captured, if any
    std::unique_ptr<MoveNode> next; // Pointer to the next move
    MoveNode* prev; // Pointer to the previous move

    // Constructor to initialize a MoveNode
    MoveNode(int sx, int sy, int ex, int ey, std::unique_ptr<Piece> captured)
        : startX(sx), startY(sy), endX(ex), endY(ey), capturedPiece(std::move(captured)), next(nullptr), prev(nullptr) {}
};

// MoveList manages the doubly linked list of moves
class MoveList {
public:
    MoveList() : head(nullptr), current(nullptr) {}
    ~MoveList() { clear(); }

    // Adds a move to the list
    void addMove(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> capturedPiece) {
        auto newNode = std::make_unique<MoveNode>(startX, startY, endX, endY, std::move(capturedPiece));
        if (!head) {
            head = std::move(newNode); // If list is empty, new move becomes the head
            current = head.get(); // Set current to head
        }
        else {
            current->next = std::move(newNode); // Add new move after current one
            current->next->prev = current; // Link back to current move
            current = current->next.get(); // Move current to the new move
        }
    }

    // Undo the last move and return it
    MoveNode* undo() {
        if (current) {
            current = current->prev; // Move current back
            return current ? current->next.get() : head.get(); // Return the move to be undone
        }
        return nullptr; // No moves to undo
    }

    // Redo the next move and return it
    MoveNode* redo() {
        if (current && current->next) {
            current = current->next.get(); // Move current forward
            return current; // Return the move to be redone
        }
        return nullptr; // No moves to redo
    }

    // Clear the list
    void clear() {
        while (head) {
            head = std::move(head->next); // Delete moves one by one
        }
        current = nullptr; // Reset current
    }

private:
    std::unique_ptr<MoveNode> head; // Pointer to the first move
    MoveNode* current; // Pointer to the current move
};

#endif // MOVELIST_H
