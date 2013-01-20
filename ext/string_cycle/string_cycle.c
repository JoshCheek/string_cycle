#include <ruby.h>

typedef struct linked_list_node {
  char                      c;
  struct linked_list_node*  next;
} SCLinkedListNode;

typedef struct {
  SCLinkedListNode*  head;
  SCLinkedListNode*  tail;
  int                size;
} SCLinkedList;

SCLinkedListNode* sc_new_linked_list_node(char c, SCLinkedListNode* next_node) {
  SCLinkedListNode* new_node = (SCLinkedListNode*) malloc(sizeof(SCLinkedListNode));
  new_node->c               = c;
  new_node->next            = next_node;
  return new_node;
}

SCLinkedList* sc_new_linked_list() {
  SCLinkedList* new_list = (SCLinkedList*) malloc(sizeof(SCLinkedList));
  new_list->head         = NULL;
  new_list->tail         = NULL;
  new_list->size         = 0;
  return new_list;
}

void sc_free_linked_list(void *p) {
  SCLinkedList*     list         = p;
  SCLinkedListNode* prev_node    = NULL;
  SCLinkedListNode* current_node = list->head;
  while(current_node) {
    prev_node    = current_node;
    current_node = current_node->next;
    free(prev_node);
  }
  free(list);
}

void append_char(SCLinkedList* list, char c) {
  SCLinkedListNode* node = sc_new_linked_list_node(c, NULL);
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

static VALUE sc_alloc(VALUE klass) {
  return Data_Wrap_Struct(klass, 0, sc_free_linked_list, sc_new_linked_list());
}

// need to convert to the data structure
static VALUE sc_initialize(VALUE self, VALUE string_to_cycle) {
  // figure out how to do: string_to_cycle.each_char { |c| append_char(list, c) }
  SCLinkedList* list;
  Data_Get_Struct(self, SCLinkedList, list);

  // just storing the list to show that this code actually does something
  // after figuring out how to put it into the list data structure, though,
  // this should be removed
  return rb_iv_set(self, "@list", string_to_cycle);
}

// need to convert back to Ruby string
VALUE sc_to_s(VALUE self) {
  return rb_iv_get(self, "@list");
}

void Init_string_cycle() {
  VALUE StringCycle = rb_define_class("StringCycle", rb_cObject);
  rb_define_alloc_func(StringCycle, sc_alloc);
  rb_define_method(StringCycle, "initialize", sc_initialize, 1);
  rb_define_method(StringCycle, "to_s",       sc_to_s,       0);
}
