TP de Synthèse – Ensea in the Shell

Objectifs : Réaliser un micro shell, affichant les codes de sortie et les temps d’exécution des programmes lancés.

Le développement d'un micro shell, "enseash", a été entrepris dans le cadre du projet. L'objectif principal de ce micro shell est de permettre l'exécution de commandes tout en fournissant des informations détaillées sur leur déroulement. Ce micro shell offre une interface simplifiée pour lancer des commandes, ainsi qu'un retour d'informations immédiat sur leur exécution.

Exercice 1 (Micro Shell de Base):

Affichage d’un message d’accueil, suivi d’un prompt simple.

Dans cet exercice, nous avons créé la base du micro shell, en commençant par afficher un message d'accueil et un prompt simple. Le code source ci-dessous illustre la mise en œuvre de cette fonctionnalité initiale.

Explications:

- La fonction displayPrompt est responsable de l'affichage du message d'accueil et du prompt du shell. Le message d'accueil informe l'utilisateur sur l'utilisation du shell et la manière de le quitter. Le prompt est représenté par enseash %%.
- Nous utilisons la fonction write pour écrire le message d'accueil dans la sortie standard (STDOUT\_FILENO.

Exercice 2 (Exécution de Commandes):

Dans cet exercice, nous avons ajouté la capacité d'exécuter des commandes saisies par l'utilisateur dans le micro shell.

Explications :

- La fonction executeCommand est responsable de la lecture de la commande entrée par l'utilisateur. Elle affiche également le prompt enseash%% pour indiquer à l'utilisateur qu'il peut saisir une commande.
- Nous utilisons write pour afficher le prompt et read pour obtenir la commande de l'utilisateur.
- À chaque itération de la boucle, un nouvel enfant est créé à l'aide de fork().
- Le processus parent attend que le processus enfant se termine à l'aide de wait. Une fois que l'exécution est terminée, le prompt est réinitialisé et la boucle continue

Avant de retourner la commande, nous nous assurons de supprimer le caractère de nouvelle ligne à la fin de la chaîne pour éviter des problèmes lors de l'exécution.

Exercice 3 (Gestion de la sortie du shell avec la commande “exit” ou un <ctrl>+d): 

Dans cet exercice, nous avons ajouté la fonctionnalité permettant de quitter le micro shell en saisissant la commande "exit" ou en atteignant la fin du fichier d'entrée (EOF) avec la combinaison de touches Ctrl+D.

Explications :

- Nous avons ajouté une vérification après la récupération de la commande à l'intérieur de la boucle principale. Si la commande est "exit" ou si sa longueur est nulle, le micro shell affiche "Bye bye..." et quitte la boucle, terminant ainsi l'exécution du programme.

Exercice 4 (Affichage du code de retour (ou du signal) de la commande précédente dans le prompt): 

Dans cet exercice, nous avons ajouté la fonctionnalité qui affiche le code de retour (ou le signal) de la commande précédente dans le prompt.

Explications :

- Nous avons ajouté une variable status pour stocker le statut de la commande exécutée par le processus fils. Cela inclut le code de retour si la commande se termine correctement ou le signal si elle est interrompue.
- Après l'exécution de la commande, le processus parent utilise les macros WIFEXITED et WEXITSTATUS pour vérifier si le processus fils s'est terminé correctement et pour obtenir le code de retour.

Exercice 5 (Mesure du temps d’exécution de la commande en utilisant l’appel clock\_gettime):

Dans cet exercice, nous avons ajouté la mesure du temps d'exécution de la commande en utilisant l'appel système clock\_gettime.

Explications :

- Nous avons ajouté deux structures struct timespec, t\_init\_child et t\_finish\_child, pour stocker le temps de début et de fin de l'exécution du processus enfant.
- Avant de lancer le processus enfant, nous utilisons clock\_gettime pour obtenir le temps de début (t\_init\_child).

- Après l'exécution du processus enfant, nous utilisons à nouveau clock\_gettime pour obtenir le temps de fin (t\_finish\_child).
- Nous calculons ensuite la différence entre ces deux temps pour obtenir le temps total d'exécution de la commande en millisecondes.

Exercice 6 Exécution d’une commande complexe (avec arguments) :

Dans cet exercice, nous avons étendu notre micro-shell pour prendre en charge l'exécution de commandes complexes avec des arguments.

Explications :

- Nous avons ajouté la fonction parseArguments qui prend la commande complète et la divise en tokens (commande et arguments) pour les stocker dans un tableau d'arguments.
- Nous avons modifié la boucle principale pour lire et exécuter les commandes avec des arguments.
- Dans le processus enfant, nous utilisons execvp pour exécuter la commande avec les arguments.
- La sortie du temps d'exécution et du statut reste inchangée par rapport à l'exercice précédent.

Exercice 7 Gestion des redirections vers stdin et stdout avec ‘<’ et ‘>’ ;

Dans cet exercice, nous avons ajouté la gestion des redirections de fichiers avec les symboles ‘<’ et ‘>’ pour rediriger respectivement l'entrée standard (stdin) et la sortie standard (stdout) d'une commande.

Explications :

- Nous avons ajouté une gestion de redirection en utilisant les fonctions open, dup2, et close. Ces fonctions permettent de rediriger respectivement l'entrée standard (stdin) et la sortie standard (stdout) de la commande.
- Un fichier texte est créé et contient la commande que nous avons entré.
