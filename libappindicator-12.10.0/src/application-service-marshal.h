
#ifndef ___application_service_marshal_MARSHAL_H__
#define ___application_service_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:STRING,INT,STRING,STRING,STRING,STRING,STRING (./application-service-marshal.list:19) */
extern void _application_service_marshal_VOID__STRING_INT_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                              GValue       *return_value,
                                                                                              guint         n_param_values,
                                                                                              const GValue *param_values,
                                                                                              gpointer      invocation_hint,
                                                                                              gpointer      marshal_data);

/* VOID:INT,STRING,STRING (./application-service-marshal.list:20) */
extern void _application_service_marshal_VOID__INT_STRING_STRING (GClosure     *closure,
                                                                  GValue       *return_value,
                                                                  guint         n_param_values,
                                                                  const GValue *param_values,
                                                                  gpointer      invocation_hint,
                                                                  gpointer      marshal_data);

/* VOID:INT,STRING (./application-service-marshal.list:21) */
extern void _application_service_marshal_VOID__INT_STRING (GClosure     *closure,
                                                           GValue       *return_value,
                                                           guint         n_param_values,
                                                           const GValue *param_values,
                                                           gpointer      invocation_hint,
                                                           gpointer      marshal_data);

/* VOID:STRING,STRING (./application-service-marshal.list:22) */
extern void _application_service_marshal_VOID__STRING_STRING (GClosure     *closure,
                                                              GValue       *return_value,
                                                              guint         n_param_values,
                                                              const GValue *param_values,
                                                              gpointer      invocation_hint,
                                                              gpointer      marshal_data);

/* VOID:BOOL,STRING,OBJECT (./application-service-marshal.list:23) */
extern void _application_service_marshal_VOID__BOOLEAN_STRING_OBJECT (GClosure     *closure,
                                                                      GValue       *return_value,
                                                                      guint         n_param_values,
                                                                      const GValue *param_values,
                                                                      gpointer      invocation_hint,
                                                                      gpointer      marshal_data);
#define _application_service_marshal_VOID__BOOL_STRING_OBJECT	_application_service_marshal_VOID__BOOLEAN_STRING_OBJECT

/* VOID:INT,UINT (./application-service-marshal.list:24) */
extern void _application_service_marshal_VOID__INT_UINT (GClosure     *closure,
                                                         GValue       *return_value,
                                                         guint         n_param_values,
                                                         const GValue *param_values,
                                                         gpointer      invocation_hint,
                                                         gpointer      marshal_data);

/* VOID:INT,INT (./application-service-marshal.list:25) */
extern void _application_service_marshal_VOID__INT_INT (GClosure     *closure,
                                                        GValue       *return_value,
                                                        guint         n_param_values,
                                                        const GValue *param_values,
                                                        gpointer      invocation_hint,
                                                        gpointer      marshal_data);

G_END_DECLS

#endif /* ___application_service_marshal_MARSHAL_H__ */

