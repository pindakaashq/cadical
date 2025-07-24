#ifndef _ccadical_h_INCLUDED
#define _ccadical_h_INCLUDED

/*------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// C wrapper for CaDiCaL's C++ API following IPASIR.

typedef struct CCaDiCaL CCaDiCaL;

const char *ccadical_signature (void);
CCaDiCaL *ccadical_init (void);
void ccadical_release (CCaDiCaL *);

void ccadical_add (CCaDiCaL *, int lit);
void ccadical_assume (CCaDiCaL *, int lit);
int ccadical_solve (CCaDiCaL *);
int ccadical_val (CCaDiCaL *, int lit);
int ccadical_failed (CCaDiCaL *, int lit);

void ccadical_set_terminate (CCaDiCaL *, void *state,
                             int (*terminate) (void *state));

void ccadical_set_learn (CCaDiCaL *, void *state, int max_length,
                         void (*learn) (void *state, int *clause));

/*------------------------------------------------------------------------*/

// C wrapper for CaDiCaL's C++ API following IPASIR-UP.

struct _CExternalPropagator {
  void *data;
  bool is_lazy;
  bool are_reasons_forgettable;
  void (*notify_assignments)(void *data, const int *lits, size_t size);
  void (*notify_new_decision_level)(void *data);
  void (*notify_backtrack)(void *data, size_t new_level);
  bool (*check_found_model)(void *data, const int *model, size_t size);
  int (*decide)(void *data);
  int (*propagate)(void *data);
  int (*add_reason_clause_lit)(void *data, int propagated_lit);
  bool (*has_external_clause)(void *data, bool *is_forgettable);
  int (*add_external_clause_lit)(void *data);
};
typedef struct _CExternalPropagator CExternalPropagator;

extern const CExternalPropagator empty_propagator;

void ccadical_connect_external_propagator(CCaDiCaL *, CExternalPropagator prop);
void ccadical_disconnect_external_propagator(CCaDiCaL *);

void ccadical_add_observed_var(CCaDiCaL *, int var);
void ccadical_remove_observed_var(CCaDiCaL *, int var);
void ccadical_reset_observed_vars(CCaDiCaL *);
bool ccadical_is_decision(CCaDiCaL *, int lit);
void ccadical_force_backtrack(CCaDiCaL *, size_t new_level);

/*------------------------------------------------------------------------*/

// Non-IPASIR conformant 'C' functions.

void ccadical_constrain (CCaDiCaL *, int lit);
int ccadical_constraint_failed (CCaDiCaL *);
void ccadical_set_option (CCaDiCaL *, const char *name, int val);
void ccadical_limit (CCaDiCaL *, const char *name, int limit);
int ccadical_get_option (CCaDiCaL *, const char *name);
void ccadical_print_statistics (CCaDiCaL *);
int64_t ccadical_active (CCaDiCaL *);
int64_t ccadical_irredundant (CCaDiCaL *);
int ccadical_fixed (CCaDiCaL *, int lit);
int ccadical_trace_proof (CCaDiCaL *, FILE *, const char *);
void ccadical_close_proof (CCaDiCaL *);
void ccadical_conclude (CCaDiCaL *);
void ccadical_terminate (CCaDiCaL *);
void ccadical_freeze (CCaDiCaL *, int lit);
int ccadical_frozen (CCaDiCaL *, int lit);
void ccadical_melt (CCaDiCaL *, int lit);
int ccadical_simplify (CCaDiCaL *);

/*------------------------------------------------------------------------*/

// [PATCH] Additional C bindings for C++ Cadical

CCaDiCaL *ccadical_copy(CCaDiCaL *slv);
void ccadical_phase(CCaDiCaL *, int lit);
void ccadical_unphase(CCaDiCaL *, int lit);

/*------------------------------------------------------------------------*/

// Support legacy names used before moving to more IPASIR conforming names.

#define ccadical_reset ccadical_release
#define ccadical_sat ccadical_solve
#define ccadical_deref ccadical_val

/*------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
/*------------------------------------------------------------------------*/

#endif
