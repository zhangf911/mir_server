//
// ensure.hpp
//
// Copyright (c) Nous Xiong.
//
// Macro ENSURE impl.
//

#ifndef ENSURE_HPP
#define ENSURE_HPP

#ifdef ENSURE_HAS_BOOST

#include <boost/exception/all.hpp>
#include <boost/thread/tss.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/integer.hpp>
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace un
{
/// 运行时刻信息
typedef boost::error_info<struct tag_runtime, std::string> errinfo_runtime_t;

/// 专用于ensure的异常信息
typedef boost::error_info<struct tag_ensure, std::string> errinfo_ensure_t;

/// 异常基类
class exception
  : public virtual std::exception
  , public virtual boost::exception
{
};

class ensure
{
public:
  ensure()
    : current_function_(0)
    , file_(0)
    , line_(-1)
    , msg_(0)
  {
  }

  ~ensure()
  {
  }

public:
  ensure& set_context(char const* expr, char const* current_function, char const* file, int line)
  {
    msg_ = 0;
    err_.str("");
    err_ << "Ensure failed, expression: '" << expr << "', values: ";
    current_function_ = current_function;
    file_ = file;
    line_ = line;

    // 这里你可以将std::cerr替换为你自己项目的日志系统
    std::cerr <<
      "Ensure failed point: [" << file_ << "]=[" << line_ << "]" << std::endl;
    return *this;
  }

  ensure& set_current_val(boost::int8_t src, char const* name)
  {
    boost::int32_t tmp = (boost::int32_t)src;
    return set_val(tmp, name);
  }
  ensure& set_current_val(bool src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(boost::int16_t src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(boost::uint16_t src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(boost::int32_t src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(boost::uint32_t src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(boost::int64_t src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(boost::uint64_t src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(std::string const& src, char const* name)
  {
    err_ << name << " = " << src << ", size: " << src.size() << "; ";
    return *this;
  }
  // 你可以加入任何你项目需要的数据类型
  // 例如：
  //ensure& set_current_val(my_data const& src, char const* name)
  //{
  //  err_ << name << " = " << src.get_xxx() << "; ";
  //  return *this;
  //}

  /// 用户可添加的消息
  ensure& set_current_val(char const* msg, char const*)
  {
    msg_ = msg;
    return *this;
  }

  /// 抛出异常
  template <typename ExceptT>
  ensure& set_current_val(ExceptT const& ex, char const*)
  {
    if (msg_)
    {
      ex << errinfo_runtime_t(msg_);
    }
    ex << errinfo_ensure_t(err_.str());
    boost::exception_detail::throw_exception_(ex, current_function_, file_, line_);
    return *this;
  }

  static ensure& get_ensure()
  {
    // 为了多线程下方便的使用ensure，这里使用了线程本地存储，
    // 如果是单线程程序，这里可以直接换为static ensure e;
    static boost::thread_specific_ptr<ensure> this_ens;
    ensure* ret = this_ens.get();
    if (!ret)
    {
      this_ens.reset(new ensure);
      ret = this_ens.get();
    }
    return *ret;
  }

private:
  template <typename T>
  ensure& set_val(T const t, char const* name)
  {
    err_ << name << " = " << t << "; ";
    return *this;
  }

private:
  std::stringstream err_;
  char const* current_function_;
  char const* file_;
  int line_;
  char const* msg_;
};
}

#define ENSURE_OP_IMPL(e, elem) e.set_current_val((elem), #elem); // 必须要定义这个宏，不然#elem无法正确的显示变量的字符串形式
#define ENSURE_OP(COLA_ENS, e, elem) ENSURE_OP_IMPL(e, elem)

#define ENSURE(expr, args) \
  if( (expr) ) ; \
  else \
  { \
    un::ensure& e = un::ensure::get_ensure(); \
    e.set_context(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__); \
    BOOST_PP_SEQ_FOR_EACH(ENSURE_OP, e, args); \
  }

#else

#include <stdexcept>
#include <sstream>
#include <iostream>

namespace un
{
class ensure
{
public:
  ensure()
    : ENSURE_A(*this)
    , ENSURE_B(*this)
    , file_(0)
    , line_(-1)
    , msg_(0)
  {
  }

  ~ensure()
  {
  }

  ensure& ENSURE_A;
  ensure& ENSURE_B;

public:
  ensure& set_context(char const* expr, char const* file, int line)
  {
    msg_ = 0;
    err_.str("");
    err_ << "Ensure failed, expression: '" << expr << "', values: ";
    file_ = file;
    line_ = line;

    // 这里你可以将std::cerr替换为你自己项目的日志系统
    std::cerr <<
      "Ensure failed point: [" << file_ << "]=[" << line_ << "]" << std::endl;
    return *this;
  }

  ensure& set_current_val(char src, char const* name)
  {
    int tmp = (int)src;
    return set_val(tmp, name);
  }
  ensure& set_current_val(bool src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(short src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(int src, char const* name)
  {
    return set_val(src, name);
  }
  ensure& set_current_val(std::string const& src, char const* name)
  {
    err_ << name << " = " << src << ", size: " << src.size() << "; ";
    return *this;
  }
  // 你可以加入任何你项目需要的数据类型
  // 例如：
  //ensure& set_current_val(my_data const& src, char const* name)
  //{
  //  err_ << name << " = " << src.get_xxx() << "; ";
  //  return *this;
  //}

  /// 用户可添加的消息
  ensure& set_current_val(char const* msg, char const*)
  {
    msg_ = msg;
    return *this;
  }

  /// 抛出异常
  template <typename ExceptT>
  ensure& set_current_val(ExceptT const& ex, char const*)
  {
    if (msg_)
    {
      err_ << "user msg = " << msg_;
    }
    ex.set_error(err_.str()); // 需要用户实现这个方法
    throw ex;
    return *this;
  }

  static ensure& get_ensure()
  {
    // 仅仅单线程
    static ensure ret;
    return ret;
  }

private:
  template <typename T>
  ensure& set_val(T const t, char const* name)
  {
    err_ << name << " = " << t << "; ";
    return *this;
  }

private:
  std::stringstream err_;
  char const* file_;
  int line_;
  char const* msg_;
};
}

#define ENSURE_A(x) ENSURE_OP(x, B)
#define ENSURE_B(x) ENSURE_OP(x, A)

#define ENSURE_OP(x, next) \
  ENSURE_A.set_current_val((x), #x).ENSURE_##next

#define ENSURE(expr) \
  if( (expr) ) ; \
  else un::ensure::get_ensure().set_context(#expr,__FILE__,__LINE__).ENSURE_A

#endif

#endif /* COLA_ENSURE_HPP */
