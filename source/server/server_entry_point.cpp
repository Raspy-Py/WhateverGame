#include "whatever_server.h"

int main(){
  WhateverServer server(8080, {8888, 8889, 8890});

  server.Start();
  server.StartBroadcasting();

  server.WaitForStopSignal();

  server.StopBroadcasting();
  server.Stop();

  return 0;
}