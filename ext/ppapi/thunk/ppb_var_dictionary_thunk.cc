// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ppapi/c/dev/ppb_var_dictionary_dev.h"
#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/shared_impl/dictionary_var.h"
#include "ppapi/shared_impl/proxy_lock.h"
#include "ppapi/thunk/thunk.h"

namespace ppapi {
namespace thunk {

namespace {

PP_Var Create() {
  ProxyAutoLock lock;

  // Var tracker will hold a reference to this object.
  DictionaryVar* var = new DictionaryVar();
  return var->GetPPVar();
}

PP_Var Get(PP_Var dict, PP_Var key) {
  ProxyAutoLock lock;

  DictionaryVar* dict_var = DictionaryVar::FromPPVar(dict);
  if (!dict_var)
    return PP_MakeUndefined();
  return dict_var->Get(key);
}

PP_Bool Set(PP_Var dict, PP_Var key, PP_Var value) {
  ProxyAutoLock lock;

  DictionaryVar* dict_var = DictionaryVar::FromPPVar(dict);
  if (!dict_var)
    return PP_FALSE;

  return dict_var->Set(key, value);
}

void Delete(PP_Var dict, PP_Var key) {
  ProxyAutoLock lock;

  DictionaryVar* dict_var = DictionaryVar::FromPPVar(dict);
  if (dict_var)
    dict_var->Delete(key);
}

PP_Bool HasKey(PP_Var dict, PP_Var key) {
  ProxyAutoLock lock;

  DictionaryVar* dict_var = DictionaryVar::FromPPVar(dict);
  if (!dict_var)
    return PP_FALSE;
  return dict_var->HasKey(key);
}

PP_Var GetKeys(PP_Var dict) {
  ProxyAutoLock lock;

  DictionaryVar* dict_var = DictionaryVar::FromPPVar(dict);
  if (!dict_var)
    return PP_MakeNull();
  return dict_var->GetKeys();
}

const PPB_VarDictionary_Dev_0_1 g_ppb_vardictionary_0_1_thunk = {
  &Create,
  &Get,
  &Set,
  &Delete,
  &HasKey,
  &GetKeys
};

}  // namespace

const PPB_VarDictionary_Dev_0_1* GetPPB_VarDictionary_Dev_0_1_Thunk() {
  return &g_ppb_vardictionary_0_1_thunk;
}

}  // namespace thunk
}  // namespace ppapi
