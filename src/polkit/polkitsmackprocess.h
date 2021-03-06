/*
 * Copyright (C) 2014 Intel, Inc.
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

#if !defined (_POLKIT_COMPILATION) && !defined(_POLKIT_INSIDE_POLKIT_H)
#error "Only <polkit/polkit.h> can be included directly, this file may disappear or change contents."
#endif

#ifndef __POLKIT_SMACK_PROCESS_H
#define __POLKIT_SMACK_PROCESS_H

#include <glib-object.h>
#include <polkitunixprocessprivate.h>
#include <polkit/polkittypes.h>

G_BEGIN_DECLS

#define POLKIT_TYPE_SMACK_PROCESS          (polkit_smack_process_get_type())
#define POLKIT_SMACK_PROCESS(o)            (G_TYPE_CHECK_INSTANCE_CAST ((o), POLKIT_TYPE_SMACK_PROCESS, PolkitSmackProcess))
#define POLKIT_SMACK_PROCESS_CLASS(k)      (G_TYPE_CHECK_CLASS_CAST((k), POLKIT_TYPE_SMACK_PROCESS, PolkitSmackProcessClass))
#define POLKIT_SMACK_PROCESS_GET_CLASS(o)  (G_TYPE_INSTANCE_GET_CLASS ((o), POLKIT_TYPE_SMACK_PROCESS, PolkitSmackProcessClass))
#define POLKIT_IS_SMACK_PROCESS(o)         (G_TYPE_CHECK_INSTANCE_TYPE ((o), POLKIT_TYPE_SMACK_PROCESS))
#define POLKIT_IS_SMACK_PROCESS_CLASS(k)   (G_TYPE_CHECK_CLASS_TYPE ((k), POLKIT_TYPE_SMACK_PROCESS))

#if 0
typedef struct _PolkitSmackProcess PolkitSmackProcess;
#endif
typedef struct _PolkitSmackProcessClass PolkitSmackProcessClass;

GType          polkit_smack_process_get_type  (void) G_GNUC_CONST;
PolkitSubject *polkit_smack_process_new_full  (gint                pid,
                                               guint64             start_time,
                                               gint                uid,
                                               const gchar        *label);
char*           polkit_smack_process_get_label (PolkitSmackProcess *process);
void            polkit_smack_process_set_label (PolkitSmackProcess *process,
                                                const gchar        *label);


G_END_DECLS

#endif /* __POLKIT_SMACK_PROCESS_H */
