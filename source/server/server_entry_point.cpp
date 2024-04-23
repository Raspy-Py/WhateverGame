#include "whatever_server.h"

int main(){
  WhateverServer server(8080, 8888);

  server.Start();
  server.StartBroadcasting();
  server.Join();

  return 0;
}