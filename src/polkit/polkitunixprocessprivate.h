/*
 * Copyright (C) 2014 Intel, inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Michael Leibowitz <michael.leibowitz@intel.com>
 */

#ifndef __POLKIT_UNIX_PROCESS_PRIVATE_H
#define __POLKIT_UNIX_PROCESS_PRIVATE_H

/**
 * PolkitUnixProcess:
 *
 * The #PolkitUnixProcess struct should not be accessed directly.
 */
struct _PolkitUnixProcess
{
  GObject parent_instance;

  gint pid;
  guint64 start_time;
  gint uid;
};

struct _PolkitUnixProcessClass
{
  GObjectClass parent_class;
};

#endif /* __POLKIT_UNIX_PROCESS_PRIVATE_H */
