#include <ruby.h>

// change these to CamelCase
typedef struct linked_list_node {
  char                      c;
  struct linked_list_node*  next;
} linked_list_node;

typedef struct {
  linked_list_node*  head;
  linked_list_node*  tail;
  int                size;
} linked_list;

linked_list_node* new_linked_list_node(char c, linked_list_node* next_node) {
  linked_list_node* new_node = (linked_list_node*) malloc(sizeof(linked_list_node));
  new_node->c                = c;
  new_node->next             = next_node;
  return new_node;
}

linked_list* new_linked_list() {
  linked_list* new_list = (linked_list*) malloc(sizeof(linked_list));
  new_list->head        = NULL;
  new_list->tail        = NULL;
  new_list->size        = 0;
  return new_list;
}

void free_linked_list(void *p) {
  linked_list*      list         = p;
  linked_list_node* prev_node    = NULL;
  linked_list_node* current_node = list->head;
  while(current_node) {
    prev_node = current_node;
    current_node = current_node->next;
    free(prev_node);
  }
  free(list);
}

void append_char(linked_list* list, char c) {
  linked_list_node* node = new_linked_list_node(c, NULL);
  if(list->size == 0)
    list->head = node;
  else
    list->tail->next = node;
  list->tail = node;
  ++(list->size);
}

/*
static VALUE cd_alloc(VALUE klass) {
  CDJukebox *jukebox;
  VALUE obj;
  // Vendor library creates the Jukebox
  jukebox = new_jukebox();
  // then we wrap it inside a Ruby CDPlayer object
  obj = Data_Wrap_Struct(klass, 0, cd_free, jukebox);
  return obj;
}
void Init_CDPlayer() {
  cCDPlayer = rb_define_class("CDPlayer", rb_cObject);
  rb_define_alloc_func(cCDPlayer, cd_alloc);
  // ...
}
static VALUE cd_initialize(VALUE self, VALUE unit) {
  int unit_id;
  CDJukebox *jb;
  Data_Get_Struct(self, CDJukebox, jb);
  unit_id = NUM2INT(unit);
  assign_jukebox(jb, unit_id);
  return self;
}
*/

static VALUE string_cycle_alloc(VALUE klass) {
  return Data_Wrap_Struct(klass, 0, free_linked_list, new_linked_list());
}

// need to convert to the data structure
static VALUE string_cycle_initialize(VALUE self, VALUE string_to_cycle) {
  linked_list* list;
  Data_Get_Struct(self, linked_list, list);
  return rb_iv_set(self, "@list", string_to_cycle);
}

// need to convert back to Ruby string
VALUE string_cycle_to_s(VALUE self) {
  return rb_iv_get(self, "@list");
}

void Init_string_cycle() {
  VALUE StringCycle = rb_define_class("StringCycle", rb_cObject);
  rb_define_alloc_func(StringCycle, string_cycle_alloc);
  rb_define_method(StringCycle, "initialize", string_cycle_initialize, 1);
  rb_define_method(StringCycle, "to_s",       string_cycle_to_s,       0);
}
