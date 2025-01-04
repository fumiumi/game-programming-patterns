#include <iostream>
#include <list>
#include <algorithm>

// ダミーの Entity と Event (必要に応じて定義を拡張)
struct Entity {
    int id;
};

enum class Event {
    Created,
    Updated,
    Destroyed
};

// 前方宣言 (Subject, Observer) 
class Subject;
class Observer;

/* =========================
 *  Observerクラスの定義
 * ========================= */

class Observer {
public:
    // 仮想デストラクタ
    virtual ~Observer() = default;

    // 通常の更新通知
    virtual void OnNotify(const Entity& entity, Event event) = 0;

    // Subject 破棄の通知
    // これを受け取ったら、Observer は Subject に触らないようにする
    virtual void OnSubjectDestroy(Subject* subject) = 0;
};

/* =========================
 *  Subjectクラスの定義
 * ========================= */

class Subject {
public:
    ~Subject() {
        // デストラクタで Observer たちに「自分は破棄されるよ」と通知する
        for (auto* observer : observers_) {
            observer->OnSubjectDestroy(this);
        }
        // 通知が終わったら、リストを空にしておく
        // (もはや Subject 自体も破棄されるので不要ですが、念のため)
        observers_.clear();
    }

    // Observer 登録
    void AddObserver(Observer* observer) {
        // 同じ Observer が重複して登録されないようにする例
        auto it = std::find(observers_.begin(), observers_.end(), observer);
        if (it == observers_.end()) {
            observers_.push_back(observer);
        }
    }

    // Observer 解除
    void RemoveObserver(Observer* observer) {
        observers_.remove(observer);
    }

    // イベント発生時の通知
    void Notify(const Entity& entity, Event event) {
        for (auto* observer : observers_) {
            observer->OnNotify(entity, event);
        }
    }

private:
    std::list<Observer*> observers_;
};

/* =========================
 *  具体的なObserver例
 * ========================= */

class MyObserver : public Observer {
public:
    // コンストラクタで Subject と紐づける
    MyObserver(Subject* subject)
        : subject_(subject)
    {
        if (subject_) {
            subject_->AddObserver(this);
        }
    }

    // デストラクタ
    ~MyObserver() override {
        // MyObserver が先に破棄される場合は、
        // 登録解除のため Subject をまだ参照できるかを確認
        if (subject_) {
            subject_->RemoveObserver(this);
        }
    }

    // 通常の通知を受け取ったときの動作
    void OnNotify(const Entity& entity, Event event) override {
        std::cout << "[MyObserver] OnNotify: EntityID=" 
                  << entity.id << ", Event=" << (int)event << std::endl;
    }

    // Subject 破棄時の通知
    void OnSubjectDestroy(Subject* subject) override {
        if (subject_ == subject) {
            // もう Subject は使えないので、無効化する
            subject_ = nullptr;
            std::cout << "[MyObserver] Subject is being destroyed. Detaching.\n";
        }
    }

private:
    Subject* subject_{nullptr};
};

/* =========================
 *  テスト用のmain関数
 * ========================= */

int main() {
    // 1. Subject 作成
    Subject* subject = new Subject();

    // 2. Observer を作成し、Subject に登録
    MyObserver* observerA = new MyObserver(subject);
    MyObserver* observerB = new MyObserver(subject);

    // 3. 何かイベント発生時に、Subject が Observer に通知
    Entity e{ 123 };
    subject->Notify(e, Event::Created);

    // 4. Observer を途中で手動解除する場合 (例)
    subject->RemoveObserver(observerB);
    delete observerB;  // もう使わないので削除

    // 5. Subject を破棄 → OnSubjectDestroy() により observerA は subject_ が無効化される
    delete subject; // Subject 破棄時に OnSubjectDestroy を呼ぶ

    // 6. 残った observerA を破棄 (Subject は既にない)
    delete observerA; // subject_ == nullptr なので RemoveObserver は呼ばれない

    return 0;
}
