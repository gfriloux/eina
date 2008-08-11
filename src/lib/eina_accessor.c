/*
 * vim:ts=8:sw=3:sts=8:noexpandtab:cino=>5n-3f0^-2{2
 */
/* EINA - EFL data type library
 * Copyright (C) 2002-2008 Carsten Haitzler, Jorge Luis Zapata Muga, Cedric Bail
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "eina_accessor.h"
#include "eina_private.h"

EAPI void
eina_accessor_free(Eina_Accessor *accessor)
{
   if (accessor) accessor->free(accessor);
}

EAPI void *
eina_accessor_data_get(Eina_Accessor *accessor, unsigned int position)
{
   if (!accessor) return NULL;
   if (accessor->jump_at(accessor, position) != EINA_TRUE) return NULL;
   return accessor->get_content(accessor);
}

EAPI void *
eina_accessor_container_get(Eina_Accessor *accessor)
{
   if (!accessor) return NULL;
   return accessor->get_container(accessor);
}

EAPI void
eina_accessor_over(Eina_Accessor *accessor,
		   Eina_Each cb,
		   unsigned int start,
		   unsigned int end,
		   const void *fdata)
{
   void *container;
   void *data;
   unsigned int i = start;

   if (!accessor) return ;
   if (!(start < end)) return ;

   if (accessor->jump_at(accessor, start) != EINA_TRUE) return ;

   container = accessor->get_container(accessor);
   do {
      data = accessor->get_content(accessor);

      if (cb(container, data, (void*) fdata) != EINA_TRUE) return ;

      ++i;
   } while (i < end && accessor->jump_at(accessor, i) == EINA_TRUE);
}


