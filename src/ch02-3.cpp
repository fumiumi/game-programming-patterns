// 第2章：コマンド
// 2.3 「取り消し」と「再実行」

#include <iostream>

// 第2章：コマンド
// 2.3 「取り消し」と「再実行」

#include <iostream>
#include "lib/Actor.h"
#include <stack>
#include <memory>

//例として、ターンベースのシングルプレイヤーゲームを作成し、取り消し可能なようにしているシチュエーションを考える。

class Unit : public Actor
{
public:
  Unit() : x_(0), y_(0) {}
  ~Unit() {}

  void moveTo(int x, int y);

  int x() const { return x_; }
  int y() const { return y_; }

private:
  int x_;
  int y_;
};

class Command
{
public:
  virtual ~Command() = default;
  virtual void execute() = 0;
  //virtual void undo() = 0;
};

//ユニットを移動させるコマンド
class MoveUnitCommand : public Command
{
public:
  MoveUnitCommand(Unit* unit, int x, int y) 
  : unit_(unit), x_(x), y_(y) {}

  virtual void execute() override
  {
    unit_->moveTo(x_, y_);
  }

private:
  Unit* unit_;
  int x_;
  int y_;
};

// このようなコマンドのハンドラは以下のようになる

enum class ButtonType
{
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_LEFT,
  BUTTON_RIGHT
};

Unit* getSelectedUnit();
bool isPressed(ButtonType button);

Command* handleInput()
{
  Unit* unit = getSelectedUnit();

  if(isPressed(ButtonType::BUTTON_UP))
  {
    //ユニットを１マス動かす
    int destY = unit->y() - 1;
    return new MoveUnitCommand(unit, unit->x(), destY); //ここでは毎回新しいコマンドを生成している
  }
  else if(isPressed(ButtonType::BUTTON_DOWN))
  {
    //ユニットを１マス動かす
    int destY = unit->y() + 1;
    return new MoveUnitCommand(unit, unit->x(), destY);
  }
  else if(isPressed(ButtonType::BUTTON_LEFT))
  {
    //ユニットを１マス動かす
    int destX = unit->x() - 1;
    return new MoveUnitCommand(unit, destX, unit->y());
  }
  else if(isPressed(ButtonType::BUTTON_RIGHT))
  {
    //ユニットを１マス動かす
    int destX = unit->x() + 1;
    return new MoveUnitCommand(unit, destX, unit->y());
  }

  else
  {
    return nullptr;
  }
}

// コマンドの取り消し
class CommandWithUndo
{
public:
  virtual ~CommandWithUndo() = default;
  virtual void execute() = 0;
  virtual void undo() = 0;
};

class MoveUnitCommandWithUndo : public CommandWithUndo
{
public:
  MoveUnitCommandWithUndo(Unit* unit, int x, int y)
  : unit_(unit), x_(x), y_(y), xBefore(0), yBefore(0) {}

  virtual void execute() override
  {
    xBefore = unit_->x();// undo用に現在の位置を保存
    yBefore = unit_->y();
    unit_->moveTo(x_, y_);
  }

  virtual void undo() override
  {
    unit_->moveTo(xBefore, yBefore);// 保存した位置に戻す
  }

private:
  Unit* unit_;
  int x_;
  int y_;
  int xBefore;
  int yBefore;
};

// 多段取り消し

// MoveUnitCommandWithUndoクラス
class MoveUnitCommandWithUndo : public CommandWithUndo {
public:
    MoveUnitCommandWithUndo(Unit* unit, int x, int y)
        : unit_(unit), x_(x), y_(y), xBefore(0), yBefore(0) {}

    virtual void execute() override {
        xBefore = unit_->x(); // undo用に現在の位置を保存
        yBefore = unit_->y();
        unit_->moveTo(x_, y_);
    }

    virtual void undo() override {
        unit_->moveTo(xBefore, yBefore); // 保存した位置に戻す
    }

private:
    Unit* unit_;
    int x_;
    int y_;
    int xBefore;
    int yBefore;
};

// CommandManagerクラス: 多段取り消しの履歴管理
class CommandManager {
public:
    void executeCommand(std::unique_ptr<CommandWithUndo> command) {
        command->execute();

        undoStack.push(std::move(command));
        // 新しいコマンドが実行されたらredoスタックはクリア
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            auto command = std::move(undoStack.top());
            undoStack.pop();
            command->undo();
            redoStack.push(std::move(command));
        } else {
            std::cout << "No commands to undo.\n";
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            auto command = std::move(redoStack.top());
            redoStack.pop();
            command->execute();
            undoStack.push(std::move(command));
        } else {
            std::cout << "No commands to redo.\n";
        }
    }

private:
    std::stack<std::unique_ptr<CommandWithUndo>> undoStack;
    std::stack<std::unique_ptr<CommandWithUndo>> redoStack;
};



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
