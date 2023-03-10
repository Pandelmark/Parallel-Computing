# Parallel-Computing
Parallel Computation C programs using the Message Passing Interface tool MPICH for the corresponding university course

Στο πρόγραμμα του οποίου ο κώδικας δίνεται παρακάτω αρχικά δίνεται η επιλογή στον
χρήστην ο οποίος θα έχει τρέξει με την κατάλληλη εντολή εκτέλεσης “mpiexec -np n ./ask1” ή
“mpirun -np n ./ask1” όπου n ο αριθμός των επιθυμητών διεργασίων, ‘1’ για να συνεχίσει (ή να
ξεκινήσει εάν πρόκειται για τη πρώτη εκτέλεση) και ‘2’ για την έξοδο του προγράμματος ακόμα
κι αν δεν έχει δωθεί ποτέ πίνακας κατά την εκτέλεση του.
Η διεπαφή με τον χρήστη καθ’ όλη τη διάρκεια εκτέλεσης του προγράμματος γίνεται από την
διεργασία 0 και μόνο.
Στην περίπτωση όπου ο χρήστης επιλέξει ‘1’ θα του ζητηθούν το μέγεθος του πίνακα ‘Ν’ όπου
θα πρέπει να είναι μεγαλύτερο ή ίσο του αριθμού των τρεχούμενων διεργασιών ‘p’ και έπειτα τα
στοιχεία του πίνακα.
Αυτό που θα κάνει το πρόγραμμα στη συνέχεια είναι να μοιράσει ισόποσα στην κάθε
διεργασία παιδί (rank>0) τις τιμές του πίνακα ‘Τ’ μέσω διεργασία γονέα (root) με rank = 0
κρατώντας το πρώτο μέρος του πίνακα μέρος που της αναλογεί καθώς συμμετέχει και η ίδια
στον έλεγχο των δεδομένων.
Το παραπάνω θα γίνει άμα το μέγεθος του πίνακα ‘N’ διαιρείται ακέραια με τον αριθμό των
διεργασιών ‘p’.
Όταν δεν ισχύει αυτό πάντα η διεργασία γονέας (rank=0) θα παίρνει στον τοπικό της πίνακα
‘T_loc’ τα στοιχεία που της αναλογούν καθώς και τόσα παραπάνω όσο και το υπόλοιπο της
ακέραιας διαίρεσης (N/p) ώστε να μπορέσει να γίνει ο δίκαιος μοιρασμός των στοιχείων του
πίνακα στις διεργασίες "παιδιά".
