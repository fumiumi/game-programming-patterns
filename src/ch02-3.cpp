// 第2章：コマンド
// 2.3 「取り消し」と「再実行」

#include <iostream>
#include "ch02-3.h"

int main() {
    Unit unit;

    CommandManager manager;

    // コマンドの実行
    manager.executeCommand(std::make_unique<MoveUnitCommandWithUndo>(&unit, 10, 20));
    manager.executeCommand(std::make_unique<MoveUnitCommandWithUndo>(&unit, 30, 40));
    manager.executeCommand(std::make_unique<MoveUnitCommandWithUndo>(&unit, 50, 60));

    // Undo操作
    manager.undo(); // (30, 40) に戻る
    manager.undo(); // (10, 20) に戻る

    // Redo操作
    manager.redo(); // (30, 40) に進む
    manager.redo(); // (50, 60) に進む

    return 0;
}
