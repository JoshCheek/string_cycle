#include <ruby.h>

// need to convert to the data structure
VALUE string_cycle_initialize(VALUE self, VALUE string_to_cycle) {
  return rb_iv_set(self, "@string", string_to_cycle);
}

// need to convert back to Ruby string
VALUE string_cycle_to_s(VALUE self) {
  return rb_iv_get(self, "@string");
}

void Init_string_cycle() {
  VALUE StringCycle = rb_define_class("StringCycle", rb_cObject);
  rb_define_method(StringCycle, "initialize", string_cycle_initialize, 1);
  rb_define_method(StringCycle, "to_s",       string_cycle_to_s,       0);
}
