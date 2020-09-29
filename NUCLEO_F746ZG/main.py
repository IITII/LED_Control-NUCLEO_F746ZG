import time
import logging
import network
try:
    import usocket as socket
except:
    import socket

logging.basicConfig(logging.DEBUG)
logger = logging.getLogger('led_control')

lan = network.LAN()

lan.active(True)
while True:
    logger.info('Waiting for DHCP reply...')
    time.sleep(1)
    ip, subnet, gateway, dns = lan.ifconfig()
    if ip != '0.0.0.0':
        logger.info('\tAddress: ' + ip)
        logger.info('\tSubnet Mask: ' + subnet)
        logger.info('\tGateway: ' + gateway)
        logger.info('\tDNS Server: ' + dns)
        break

server_socket = socket.socket()

address_info = socket.getaddrinfo(ip, 80)
address = address_info[0][-1]

server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(address)
server_socket.listen(5)

while True:
    client_socket, client_address = server_socket.accept()
    request_line = client_socket.readline()
    request_line_splits = str(request_line).split(' ')
    if len(request_line_splits) == 3:
        method, url, http_version = request_line_splits
        logger.info(str(method) + ' from ' + str(client_address[0]) + ' ' + url)
        path_splits = url.split('/')
        if len(path_splits) == 3:
            _, led_id, operation = path_splits
            try:
                led_id = int(led_id)
            except ValueError:
                client_socket.write('HTTP/1.0 400 Bad Request\r\n\r\n' + url + '\r\n')
            if operation == 'on':
                pyb.LED(led_id).on()
            elif operation == 'off':
                pyb.LED(led_id).off()
            elif operation == 'toggle':
                pyb.LED(led_id).toggle()
            client_socket.write('HTTP/1.0 200 OK\r\n\r\nOK\r\n')
    client_socket.close()
