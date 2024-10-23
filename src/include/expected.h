#ifndef __ETA_LANG_EXPECTED_H
#define __ETA_LANG_EXPECTED_H

template <typename T, typename E>
class Expected {
public:
  Expected(T result) {
    this->_result = result;
    this->err     = false;
  }

  Expected(E error) {
    this->_error = error;
    this->err    = true;
  }

  auto error() -> bool {
    return err;
  }

  auto result() -> bool {
    return !err;
  }

  auto get_error() -> E {
    return _error;
  }

  auto get_result() -> T {
    return _result;
  }

private:
  T _result;
  E _error;
  bool err;
};

#endif
