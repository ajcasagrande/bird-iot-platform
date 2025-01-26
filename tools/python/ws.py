#!/usr/bin/env python3
import websocket
import traceback
import sys
import time
import argparse
from threading import Thread


class WebsocketClient:
    # AUTH_HEADER = "Authorization: Basic BASIC_AUTH_TOKEN"
    # AUTH_HEADER = "Authorization: Bearer BEARER_AUTH_TOKEN"

    def __init__(self, uri, auth):
        self.done = False
        self.uri = uri
        self.auth = auth
        self.ws = websocket.create_connection(self.uri, header=[self.auth])
        self.input_thread = Thread(target=self.input, daemon=True)
        self.output_thread = Thread(target=self.output, daemon=False)

    def start(self):
        try:
            self.input_thread.start()
            self.output_thread.start()
            self.output_thread.join()
        except KeyboardInterrupt:
            print('\u001b[0m', end='')
            self.done = True
            self.ws.abort()
            self.ws.close()
            sys.exit(0)

    def output(self):
        while not self.done:
            try:
                print(self.ws.recv(), end='')
            except websocket._exceptions.WebSocketPayloadException:
                print('payload exception')
                print(traceback.format_exc())
            except websocket._exceptions.WebSocketConnectionClosedException:
                if self.done:
                    break
                print('Connection closed, attempting to reconnect in 6 seconds...')
                time.sleep(6)
                self.ws.connect(self.uri, header=[WebsocketClient.AUTH_HEADER])
            except ConnectionResetError:
                if self.done:
                    break
                print('Connection lost, attempting to reconnect...')
                self.ws.connect(self.uri, header=[WebsocketClient.AUTH_HEADER])
        print('\u001b[0m', end='')

    def input(self):
        while not self.done:
            line = sys.stdin.readline()
            if line:
                if line.strip() in ['q', 'quit', 'exit']:
                    self.done = True
                    self.ws.abort()
                    self.ws.close()
                    sys.exit(0)
                self.ws.send(line)
        print('\u001b[0m', end='')


def main():
    parser = argparse.ArgumentParser('Websocket Connector')

    parser.add_argument(
        '--port', '-p',
        dest='port',
        help='Websocket port',
        type=int,
        default=3200
    )

    parser.add_argument(
        '--protocol', '--scheme', '-s',
        dest='scheme',
        help='Websocket protocol/scheme: (ws, wss)',
        choices=['ws', 'wss'],
        default='ws'
    )

    parser.add_argument(
        '--path',
        dest='path',
        help='Websocket uri path',
        default=''
    )

    parser.add_argument(
        '--auth', '-a',
        dest='auth',
        help='Authorization header. Example: "Authorization: Basic BASIC_AUTH_TOKEN" or "Authorization: Bearer BEARER_AUTH_TOKEN"',
        default=''
    )

    parser.add_argument(
        dest='host',
        help='Websocket hostname or ip address'
    )

    args = parser.parse_args()

    uri = f'{args.scheme}://{args.host}:{args.port}{args.path}'
    print(f'Connecting to webscoket: {uri}...')
    client = WebsocketClient(uri, args.auth)
    print('Connected!')
    client.start()


if __name__ == '__main__':
    main()
