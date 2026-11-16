% orden, sigla, semestre, creditos.

% primer semestre:
asignatura(1, 'INF-129', 1, 7).
asignatura(2, 'MAT-070', 1, 6).
asignatura(3, 'MAT-060', 1, 6).
asignatura(4, 'FIS-100', 1, 6).
asignatura(5, 'HXW-006', 1, 3).
asignatura(6, 'EFI-200', 1, 2).

% segundo semestre:
asignatura(7, 'IWG-400', 2, 7).
asignatura(8, 'MAT-071', 2, 6).
asignatura(9, 'MAT-061', 2, 6).
asignatura(10, 'FIS-110', 2, 6).
asignatura(11, 'HXW-007', 2, 3).
asignatura(12, 'EFI-201', 2, 2).

% tercer semestre:
asignatura(13, 'INF-131', 3, 6).
asignatura(14, 'INF-132', 3, 5).
asignatura(15, 'MAT-081', 3, 6).
asignatura(16, 'FIS-112', 3, 6).
asignatura(17, 'HXW-008', 3, 3).
asignatura(18, 'AUX-200', 3, 4).

% cuarto semestre:
asignatura(19, 'INF-133', 4, 6).
asignatura(20, 'INF-135', 4, 6).
asignatura(21, 'MAT-053', 4, 5).
asignatura(22, 'FIS-114', 4, 6).
asignatura(23, 'HXW-009', 4, 3).
asignatura(24, 'AUX-201', 4, 4).

% quinto semestre:
asignatura(25, 'INF-138', 5, 5).
asignatura(26, 'INF-140', 5, 5).
asignatura(27, 'INF-141', 5, 5).
asignatura(28, 'INF-143', 5, 5).
asignatura(29, 'INF-229', 5, 5).
asignatura(30, 'INF-142', 5, 5).

% sexto semestre:
asignatura(31, 'INF-146', 6, 5).
asignatura(32, 'INF-145', 6, 5).
asignatura(33, 'INF-147', 6, 6).
asignatura(34, 'INF-144', 6, 6).
asignatura(35, 'INF-148', 6, 5).
asignatura(36, 'HXW-012', 6, 3).

% septimo semestre:
asignatura(37, 'INF-156', 7, 5).
asignatura(38, 'INF-154', 7, 6).
asignatura(39, 'INF-157', 7, 6).
asignatura(40, 'INF-153', 7, 5).
asignatura(41, 'INF-158', 7, 5).
asignatura(42, 'AUX-202', 7, 3). 

% octavo semestre:
asignatura(43, 'INF-165', 8, 5).
asignatura(44, 'INF-164', 8, 5).
asignatura(45, 'AUX-219', 8, 5).
asignatura(46, 'INF-166', 8, 5).
asignatura(47, 'INF-167', 8, 5).
asignatura(48, 'INF-163', 8, 5).

% noveno semestre:
asignatura(49, 'INF-302', 9, 5).
asignatura(50, 'INF-169', 9, 6).
asignatura(51, 'INF-170', 9, 6).
asignatura(52, 'INF-171', 9, 6).
asignatura(53, 'INF-168', 9, 7).

% ultimo semestre:
asignatura(54, 'INF-539', 10, 4).
asignatura(55, 'INF-540', 10, 6).
asignatura(56, 'INF-541', 10, 6).
asignatura(57, 'INF-538', 10, 14).


% sigla que es prerequisito, asignatura que se le aplica el prerequisito.

% dependencias del segundo semestre:
dependencia('MAT-070', 'MAT-071').
dependencia('MAT-060', 'MAT-061').
dependencia('FIS-100', 'FIS-110').
dependencia('HXW-006', 'HXW-007').
dependencia('EFI-200', 'EFI-201').

% dependencias del tercer semestre:
dependencia('INF-129', 'INF-131').
dependencia('MAT-070', 'INF-132').
dependencia('MAT-061', 'MAT-081').
dependencia('MAT-071', 'MAT-081').
dependencia('FIS-110', 'FIS-112').
dependencia('HXW-007', 'HXW-008').

% dependencias del cuarto semestre:
dependencia('INF-131', 'INF-133').
dependencia('INF-129', 'INF-135').
dependencia('FIS-112', 'FIS-114').
dependencia('HXW-008', 'HXW-009').
dependencia('AUX-200', 'AUX-201').

% dependencias del quinto semestre:
dependencia('INF-133', 'INF-138').
dependencia('INF-133', 'INF-140').
dependencia('INF-133', 'INF-141').
dependencia('INF-132', 'INF-143').
dependencia('INF-133', 'INF-229').
dependencia('IWG-400', 'INF-142').

% dependencias del sexto semestre:
dependencia('INF-138', 'INF-146').
dependencia('INF-140', 'INF-145').
dependencia('INF-133', 'INF-147').
dependencia('INF-133', 'INF-144').
dependencia('INF-135', 'INF-148').
dependencia('HXW-009', 'HXW-012').

% dependencias del septimo semestre:
dependencia('INF-146', 'INF-156').
dependencia('INF-140', 'INF-154').
dependencia('INF-147', 'INF-157').
dependencia('MAT-053', 'INF-153').
dependencia('INF-135', 'INF-158').
dependencia('AUX-201', 'AUX-202').

% dependencias del octavo semestre:
dependencia('INF-146', 'INF-165').
dependencia('INF-145', 'INF-164').
dependencia('INF-157', 'INF-166').
dependencia('INF-142', 'INF-167').
dependencia('INF-144', 'INF-163').

% dependencias del noveno semestre:
dependencia('AUX-219', 'INF-302').
dependencia('AUX-202', 'INF-168').

% dependencias del decimo semestre:
dependencia('INF-168', 'INF-539').
dependencia('INF-164', 'INF-538').


% 4.1. es_requisito/2

% Firma: es_requisito(+SiglaOrigen, +SiglaDestino)
% Salidas:
%   Caso 1: retorna true si un ramo es prerequisito directo (SiglaOrigen) de otro (SiglaDestino).
%   Caso 2: retorna true si un ramo es prerequisito de otro, pero de forma indirecta, es decir, si la SiglaOrigen tiene cierta dependencia con un ramo cualquiera, luego se vera si ese ramo cualquiera es prerequisito de la SiglaDestino.

es_requisito(SiglaOrigen, SiglaDestino) :- dependencia(SiglaOrigen, SiglaDestino).

es_requisito(SiglaOrigen, SiglaDestino) :- dependencia(SiglaOrigen, X), es_requisito(X, SiglaDestino).


% 4.2. ramos_inscribibles/3

% Firma: ramos_inscribibles(+Aprobados, +Semestre, -Disponibles)
% Salida: retorna una lista Disponibles con las asignaturas que si cumplen las condiciones para que un ramo sea inscribible

ramos_inscribibles(Aprobados, Semestre, Disponibles) :- 
    findall(Sigla, (
        asignatura(_, Sigla, Semestre, _), % condicion 1: la asignatura corresponde al semestre consulado
        \+ member(Sigla, Aprobados), % condicion 2: la asignatura no esta aprobada.
        \+ (dependencia(X, Sigla), \+ member(X, Aprobados)) % condicion 3: la asignatura se encuentra disponible ya que cumple que el prerequisito este aprobado y sea justamente el prerequisito correspondiente de la asignatura a colocar en la lista. 
        ), 
        Disponibles). % findall retornara una lista que sera guardada en Disponibles


% 4.3. evaluar_inscripcion/4
% Firma principal: evaluar_inscripcion(+Aprobados, +Solicitudes, -Inscritos, -Rechazados)
% Salidas: 
%   Caso 1: No hay solicitudes, por lo que entregara listas vacias en inscritos y rechazados.
%   Caso 2: La solicitud cumple o no los requerimientos y entregara las listas con los resultados correspondiente.

evaluar_inscripcion(_, [], [], []).

% Caso 2.1: el estudiante cumple los prequerimientos de la solicitud:
evaluar_inscripcion(Aprobados, [InicioSolicitud|RestoSolicitud], [InicioSolicitud|RestoInscritos], Rechazados) :- % para realizar la recursion de cola dividimos las solicitudes e inscripciones en cabeza y cola.
    \+ (dependencia(X, InicioSolicitud), \+ member(X, Aprobados)), % ve si la cabeza cumple con el prerequisito para agregarlo a la lista
    evaluar_inscripcion(Aprobados, RestoSolicitud, RestoInscritos, Rechazados). % de forma recursiva analiza el resto de la solicitud

% Caso 2.2: el estudiante no cumple con los prerequisitos de la solicitud
evaluar_inscripcion(Aprobados, [InicioSolicitud|RestoSolicitud], Inscritos, [InicioSolicitud|RestoRechazados]) :- % para realizar la recursion de cola dividimos las solicitudes y rechazos en cabeza y cola.
    (dependencia(X, InicioSolicitud), \+ member(X, Aprobados)), % ve si la cabeza no cumple con el prerequisito para agregarlo a la lista
    evaluar_inscripcion(Aprobados, RestoSolicitud, Inscritos, RestoRechazados). % de forma recursiva analiza el resto de la solicitud

% 4.4. impacto_reforma/6 
% Primero se crearon las predicados auxiliares utilizadas en esta pregunta.

% Firma: ramos_disponibles(+Aprobados, -Disponibles)
% Salida: una lista con los ramos disponibles que puede podria tomar el estudiante, esto evitara cambiar la malla
ramos_disponibles(Aprobados, Disponibles) :- 
    findall(ramo(Semestre, Orden, Sigla, Creditos), (
        asignatura(Orden, Sigla, Semestre, Creditos),
        \+ member(Sigla, Aprobados),
        \+ (dependencia(X, Sigla), \+ member(X, Aprobados))
    ), Disponibles).

% Firma: seleccionar_ramos(+Lista, +MaxCreditos, +CreditosAcumulados, -Seleccionados)
% Salida: Una lista con los ramos que se le permitira una modificacion

seleccionar_ramos([], _, _, []). % Caso 1: la lista esta vacia, por lo que los seleccionados tambien

% Caso 2: El ramo si se puede agregar 
seleccionar_ramos([ramo(_, _, Sigla, Creditos)|Resto], MaxCreditos, Acumulados, [Sigla|RestoSeleccionados]) :-
    NuevoAcumulado is Acumulados + Creditos, % debe cumplir con esta condicion
    NuevoAcumulado =< MaxCreditos,
    seleccionar_ramos(Resto, MaxCreditos, NuevoAcumulado, RestoSeleccionados).

% Caso 3: No se puede agregar.
seleccionar_ramos([ramo(_, _, _, Creditos)|Resto], MaxCreditos, Acumulados, Seleccionados) :-
    NuevoAcumulado is Acumulados + Creditos,
    NuevoAcumulado > MaxCreditos,
    seleccionar_ramos(Resto, MaxCreditos, Acumulados, Seleccionados).

% Firma: plan_optimo(+Aprobados, +MaxCreditos, -Plan)
% Salida: Entregara una lista con plan, donde se le entrega ciertos creditos para seleccionar o no ramos ademas de ordenarlos por semestre u orden entregando los mejores a seleccionar dependiendo de los creditos.
plan_optimo(Aprobados, MaxCreditos, Plan) :-
    ramos_disponibles(Aprobados, Disponibles),
    msort(Disponibles, Ordenados), % para eso usamos msort, para ordenarlos.
    seleccionar_ramos(Ordenados, MaxCreditos, 0, Plan).


% Firma: ramos_disponibles_reforma(+Aprobados, +SiglaModificada, +NuevoReq, -Disponibles)
% Salida: Una lista con los ramos disponibles pero con los nuevos prerequisitos (misma logica que con ramos_disponibles)
ramos_disponibles_reforma(Aprobados, SiglaModificada, NuevoReq, Disponibles) :-
    findall(ramo(Semestre, Orden, Sigla, Creditos), (
        asignatura(Orden, Sigla, Semestre, Creditos),
        \+ member(Sigla, Aprobados),
        \+ (dependencia(X, Sigla), \+ member(X, Aprobados)),
        \+ (Sigla = SiglaModificada, \+ member(NuevoReq, Aprobados)) % aqui estamos ingresando el nuevo prerequisito.
    ), Disponibles).

% Firma: plan_optimo_reforma(Aprobados, MaxCreditos, SiglaModificada, NuevoReq, Plan)
% Salida: retorna la lista con el mejor plan considerando los nuevos prerequisitos (misma logica que plan_optimo)
plan_optimo_reforma(Aprobados, MaxCreditos, SiglaModificada, NuevoReq, Plan) :-
    ramos_disponibles_reforma(Aprobados, SiglaModificada, NuevoReq, Disponibles),
    msort(Disponibles, Ordenados),
    seleccionar_ramos(Ordenados, MaxCreditos, 0, Plan).

% Ahora el predicadod e la pregunta 4.4:
% Firma: impacto_reforma(+Aprobados, +MaxCreditos, +SiglaModificada, +NuevoReq, -Salen, -Entran)
% Salidas: Dos listas, "Salen" y "Entran", con cada elemento correspondiente.
impacto_reforma(Aprobados, MaxCreditos, SiglaModificada, NuevoReq, Salen, Entran) :-
    plan_optimo(Aprobados, MaxCreditos, PlanOriginal), % obtenemos lo mas conveniente del plan original
    plan_optimo_reforma(Aprobados, MaxCreditos, SiglaModificada, NuevoReq, PlanReforma), % obtenemos lo mas conveniente con la nueva mejora del plan
    subtract(PlanReforma, PlanOriginal, Entran),
    subtract(PlanOriginal, PlanReforma, Salen).
    