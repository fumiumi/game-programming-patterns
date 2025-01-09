//第6章：シングルトン

// 古典的な実装
class FileSystem 
{
public:
    static FileSystem& instance()
    {
        // 遅延初期化
        if(instance_ == nullptr)
        {
            instance_ = new FileSystem();
        }
        return *instance_;
    }

private:
  // コンストラクタの隠蔽
  FileSystem() {}
  // 唯一のインスタンス
  static FileSystem* instance_;
};

// C++11以降の実装 
class NewerFileSystem 
{
public:
    static NewerFileSystem& instance()
    {
      static NewerFileSystem *instance = new NewerFileSystem();
      return *instance;
    }

private:
  // コンストラクタの隠蔽
  NewerFileSystem() {}
};

// シングルトンのサブクラス化

// まずは一般的な継承
class FileSystem
{
  public:
    virtual ~FileSystem() {}
    virtual char *read(const char *path) = 0;
    virtual void write(const char *path, char *text) = 0;
};

class PS3FileSystem : public FileSystem
{
  public:
    virtual char *read(const char *path) override
    {
      // PS3のファイルシステムを読み込む
    }

    virtual void write(const char *path, char *text) override
    {
      // PS3のファイルシステムに書き込む
    }
};

class WiiFileSystem : public FileSystem
{
  public:
    virtual char *read(const char *path) override
    {
      // Wiiのファイルシステムを読み込む
    }

    virtual void write(const char *path, char *text) override
    {
      // Wiiのファイルシステムに書き込む
    }
};

// シングルトンのサブクラス化
class FileSystem
{
  public:
    static FileSystem& instance();

    virtual ~FileSystem() {}
    virtual char *read(const char *path) = 0;
    virtual void write(const char *path, char *text) = 0;

  protected:
    FileSystem() {}
};

FileSystem& FileSystem::instance()
{
  #if PLATFORM == PLAYSTATION3
    static FileSystem *instance = new PS3FileSystem();
  #elif PLATFORM == WII
    static FileSystem *instance = new WiiFileSystem();
  #endif

  return *instance;
}