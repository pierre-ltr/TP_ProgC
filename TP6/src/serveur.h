/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

extern const char *svg_file_path;

int recois_envoie_message(int client_socket_fd, const char *data);
int renvoie_message(int client_socket_fd, const char *data);

#endif
