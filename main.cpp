#include "Lancelot.hpp"

int main()
{
  Lancelot::DatabaseHandler::GetInstance().InitConnection("tcp://localhost:3306", "root", "123456");
  return 0;
}
