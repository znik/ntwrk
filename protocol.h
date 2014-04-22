/*
 *
 *
 *
 */

#pragma once

namespace protocol {
	const int port_number = 3425;

	struct header {
		uint8_t		cmd;
		uint32_t	ver;
		uint8_t		reserved[3]; // should be 0-initialized
	};

	enum CMD {
		ECHO = 1,
		SHUTDOWN = 2,
	};
} // my_protocol
