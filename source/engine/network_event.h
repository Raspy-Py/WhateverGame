#ifndef WHATEVERGAME_SOURCE_ENGINE_NETWORK_EVENT_H_
#define WHATEVERGAME_SOURCE_ENGINE_NETWORK_EVENT_H_

enum class GameEventType{
  Default = 0,

  // Messages sent by clients
  ClientRequestConnect,         // Sent by client, who wants to connect to the server
  ClientDisconnect,             // Sent when leaving the server
  ClientUpdatePosition,         // Sent every frame to update client's data on the server side
  ClientRequestServerShutdown,  // Shuts down the server, if sent by the client, which connected first

  // Messages sent by server
  ServerApproveConnection,      // Sent as an answer to 'ClientRequestConnect', holds client's passport {id}
  ServerUpdateNetworkData,      // Sent to all clients to give them current game state
  ServerNotifyShutdown,          // Send by server before shutdown

  Count
};

#endif //WHATEVERGAME_SOURCE_ENGINE_NETWORK_EVENT_H_
