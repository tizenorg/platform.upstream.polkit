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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "polkitsmackprocess.h"
#include "polkitunixprocess.h"
#include "polkitunixprocessprivate.h"
#include "polkitsubject.h"


struct _PolkitSmackProcess
{
   PolkitUnixProcess parent_instance;

  gchar* label;
};

struct _PolkitSmackProcessClass
{
  PolkitUnixProcessClass parent_class;
};

enum
{
  PROP_0,
  PROP_LABEL
};

G_DEFINE_TYPE(PolkitSmackProcess, polkit_smack_process, POLKIT_TYPE_UNIX_PROCESS);

static void
polkit_smack_process_init (PolkitSmackProcess *smack_process)
{
  smack_process->label = NULL;
}

static void
polkit_smack_process_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  PolkitSmackProcess *smack_process = POLKIT_SMACK_PROCESS (object);

  switch (prop_id)
    {
    case PROP_LABEL:
      g_value_set_string(value, smack_process->label);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
polkit_smack_process_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  PolkitSmackProcess *smack_process = POLKIT_SMACK_PROCESS (object);

  switch (prop_id)
    {
    case PROP_LABEL:
      polkit_smack_process_set_label (smack_process, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
polkit_smack_process_class_init (PolkitSmackProcessClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->get_property = polkit_smack_process_get_property;
  gobject_class->set_property = polkit_smack_process_set_property;

  /**
   * PolkitSmackProcess:label:
   *
   * The label of the process
   */
  g_object_class_install_property (gobject_class,
				   PROP_LABEL,
				   g_param_spec_string ("label",
							"Process label",
							"The SMACK process label",
							NULL,
							G_PARAM_CONSTRUCT |
							G_PARAM_READWRITE |
							G_PARAM_STATIC_NAME |
							G_PARAM_STATIC_BLURB |
							G_PARAM_STATIC_NICK));
}

PolkitSubject *
polkit_smack_process_new_full (gint         pid,
				guint64      start_time,
				gint         uid,
				const gchar *label)
{
  return POLKIT_SUBJECT (g_object_new (POLKIT_TYPE_SMACK_PROCESS,
				       "pid", pid,
				       "start_time", start_time,
				       "uid", uid,
				       "label", label,
				       NULL));
}


/**
 * polkit_smack_process_get_label:
 * @process: A #PolkitSmackProcess.
 *
 * Gets the label for @process.
 *
 * Returns: The label for @process or NULL if unknown.  The returned
 * string is the caller's responsibility to free.
 */
char*
polkit_smack_process_get_label (PolkitSmackProcess *process)
{
  g_return_val_if_fail (POLKIT_IS_SMACK_PROCESS (process), NULL);
  return g_strdup(process->label);
}


/**
 * polkit_smack_process_set_label:
 * @process: A #PolkitSmackProcess
 * @label: The label to set for the @process or NULL to unset it.
 *
 * Sets the label for @process
 */
void
polkit_smack_process_set_label (PolkitSmackProcess *process,
				const gchar        *label)
{
  g_return_if_fail (POLKIT_IS_SMACK_PROCESS (process));
  g_return_if_fail (label == NULL);
  process->label = g_strdup(label);
}
