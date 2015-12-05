#include "dict.h"

#include <string.h>
#include <stdlib.h>
#include "logger.h"


void free_entry( data entry );


Dict* create_dict()
{
  Dict *new;
  
  new = g_new0( Dict, 1 );
  if( !new )
    return NULL;
  
  new->table = g_hash_table_new_full( g_str_hash, g_str_equal, g_free, free_entry );
  if( !new->table )
  {
    free( new );
    return NULL;
  }
  
  return new;
}


uint8 add_str_dict( Dict *dict, char *key, char* value )
{
  char *k, *v;
  Entry *e;
  
  if( !dict || !key )
    return FALSE;
 
  e = g_new0( Entry, 1 );
  if( !e )
    return FALSE;
  
  v = strdup( value );
  e->value = v;
  k = strdup( key );  
  
  if( g_hash_table_lookup( dict->table, k ) )
  {
    if( !g_hash_table_replace( dict->table, k, e ) )
    {
      free_entry( e );
      return FALSE;
    }
  }
  else
  {
    if( !g_hash_table_insert( dict->table, k, e ) )
    {
      free_entry( e );
      return FALSE;
    }
  }
  
  dict->length++;
  return TRUE;
}


uint8 add_dict_dict( Dict *dict, char *key, Dict *value )
{
  char *k;
  Entry *e;
  
  if( !dict || !key )
    return FALSE;
 
  e = g_new0( Entry, 1 );
  if( !e )
    return FALSE;
  
  e->value = value;
  e->is_dict = TRUE;
  k = strdup( key );  
  
  if( g_hash_table_lookup( dict->table, k ) )
  {
    if( !g_hash_table_replace( dict->table, k, e ) )
    {
      free_entry( e );
      return FALSE;
    }
  }
  else
  {
    if( !g_hash_table_insert( dict->table, k, e ) )
    {
      free_entry( e );
      return FALSE;
    }
  }
  
  dict->length++;
  
  return TRUE;
}


void remove_dict( Dict *dict, char *key )
{
  if( !dict || !key )
    return;
  
  if( g_hash_table_remove( dict->table, key ) )  
    dict->length--;
}


data find_dict( Dict *dict, char *key )
{
  Entry *ret;
  
  if( !dict || !key )
    return NULL;
  
  ret = ( Entry* )( g_hash_table_lookup( dict->table, key ) );
  if( !ret )
    return NULL;
  else
    return ret->value;
}


void free_dict( data dict )
{
  Dict *tmp;
  
  if( !dict )
    return;
  
  tmp = ( Dict* )( dict );
  g_hash_table_destroy( tmp->table );
  free( tmp );
}


void free_entry( data entry )
{
  Entry *tmp;
  
  if( !entry )
    return;
  
  tmp = ( Entry* )( entry );
  if( tmp->value )
  {
    if( tmp->is_dict )
      free_dict( tmp->value );
    else
      g_free( tmp->value );
  }
  
  free( tmp );
}


/*eof*/