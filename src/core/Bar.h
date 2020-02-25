#ifndef FOO_BAR_H
#define FOO_BAR_H

namespace foo {

class Bar
{
public:
  int baz() const noexcept { return m_baz; }
  Bar &baz(int a) noexcept
  {
    m_baz = a;
    return *this;
  }

private:
  int m_baz;
};

}// namespace foo

#endif