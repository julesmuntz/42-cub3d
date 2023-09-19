/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_ray_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:25:14 by gfranque          #+#    #+#             */
/*   Updated: 2023/09/19 16:45:13 by gfranque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

le rayon touche un portail:
on obtient la coordonnee du point d'impacte
en fonction de son orientation, il faut recuperer le x ou le y - sa valeur en int
recuperer le x et le y et les soustraires avec leur valeur en int (plus simple)

la nouvelle coordonnee du rayon:
en fonction de l'orientation du portail
N -> portail.x du portail + x + y (du point d'impact); portail.y (rien ne change)
S -> portail.x du portail + x + y (du point d'impact); portail.y + 1
W -> portail.x (rien ne change); portail.y du portail + x + y (du point d'impact)
E -> portail.x + 1; portail portail.y = portail.y + x + y (du point d'impact)

remplacer x et y par wallx (deja calcule)

la nouvelle direction du rayon:
fonction qui "calcul le nombre de rotations"
quatre cas:
un sur la gauche
	(P.y;-P.x)
deux sur la gauche
	(P.x;P.y)
trois sur la gauche
	(-P.y;P.x)
quatrieme sur la gauche
	(-P.x;-P.y)

*/

