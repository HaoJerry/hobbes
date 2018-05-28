
#include <hobbes/hobbes.H>
#include <hobbes/ipc/net.H>
#include <hobbes/util/array.H>
#include <hobbes/util/str.H>
#include <hobbes/util/os.H>

#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

namespace str = hobbes::str;


DEFINE_STRUCT(Order,
  (double, price),
  (double, qty)
);

typedef bool (*ValidateOrder)(const Order& order);
ValidateOrder validator;

void compileNBind()
{
  static hobbes::cc c;
  hobbes::resetMemoryPool();
  validator = c.compileFn<ValidateOrder>("order", "if(order.qty > 200.0) then false else true");
}

void processOrder(const Order& order)
{
  if (!validator(order))
  {
    std::cout << "order rejected" << std::endl;
    return;
  }
  std::cout << "order passed" << std::endl;
}

int main(int argc, char** argv)
{
  Order ord;
  ord.price = 100.0;
  ord.qty = 200.0;
  compileNBind();
  processOrder(ord);
}

