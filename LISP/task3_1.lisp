;____________________________������� 1_______________________________;
; ���� ��� ������ (a1,a2,...) � (b1,b2,...). �������� ������         ;
; (a1,b1,a2,b2,...). ���� �������� ������ ������ �����, �� �������   ;
; ����� �������� ���������.                                          ;
;____________________________________________________________________;
(defun t311(spisokA spisokB)
    (combine spisokA spisokB)
)

(defun combine(listA listB)
	(cond
		(
			(null (car listA)) 
			nil
		)
		(
			(null (car listB)) 
			(combine (cdr listA) listB)
		)
		(
			t 
		    (cons 
				(car listA) 
				(cons 
					(car listB) 
					(combine (cdr listA) (cdr listB))
				)
			)
		)
	)
)

;____________________________������� 2_______________________________;
; ���� ����������� m, n � ��������� ������. ������� �� ������        ;
; �������� � �������� � m �� n-�                                     ;
;____________________________________________________________________;

(defun t312(m n inList)
	(delete_t32 0 m n inList)
)

(defun delete_t32(idx m n inList)
	(cond
		(
			(null (car inList))
			inList
		)
		(
			(eq (atom (car inList)) nil)
			(append (cons (delete_t32 idx m n (car inList)) nil) 
					(delete_t32 (+ (cntInL (car inList) 0) (+ idx 1)) m n (cdr inList))
			)
		)
		(
			(and (>= idx m) (<= idx n)) 
		    (delete_t32 (+ idx 1) m n (cdr inList))
		)
		(
			t
			(cons 
				(car inList) (delete_t32 (+ idx 1) m n (cdr inList))
			)
		)
	)
)

;____________________________������� 3_______________________________;
; �� ������������� ������ ������� ��� ��������, �� ���������� ������ ;
;____________________________________________________________________;
(defun t313(inList)
	(delNotNumb inList)
)

(defun delNotNumb(inList)
	(cond
		(
			(atom inList) 
			inList
		)
		(
			(eq (atom (car inList)) nil) 
				(cons (delNotNumb (car inList)) (delNotNumb (cdr inList)))
		)
		(
			(numberp (car inList))
			(cons (car inList) (delNotNumb (cdr inList)))
		)
		(
			t 
			(delNotNumb (cdr inList))
		)
	)
)

;____________________________������� 4_______________________________;
; � ������� ������ �������� ��� �����-�����: ������������� �� �����  ;
; "�������������" ������������� �� ����� "�������������", ������� �� ;
; "����"                                                             ;
;____________________________________________________________________;
(defun t314(inList)
	(Change inList)
)

(defun Change(inList)
	(cond
		(
			(atom inList) 
			inList
		)
		(
			(eq (atom (car inList)) nil)
			(append (cons (Change (car inList)) nil) (Change (cdr inList)))
		)
		(
			(numberp (car inList))
			(cons (ChangeNumber (car inList)) (Change (cdr inList)))
		)
		(
			t 
			(cons (car inList) (Change (cdr inList)))
		)
	)
)

(defun ChangeNumber(num)
	(cond
		((> num 0) '�������������)
		((< num 0) '�������������)
		((eq num 0) '����)
	)
)

;____________________________������� 5_______________________________;
; � ������������ ������ ������� �������� � �������� N � M (��� ����� ;
; ������)                                                            ;
;____________________________________________________________________;
(defun t315(m n inList)
	(DeleteMN 0 m n inList)
)

(defun DeleteMN(idx m n inList)
	(cond
		(
			(null (car inList))
			inList
		)
		(
			(eq (atom (car inList)) nil)
			(append (cons (DeleteMN idx m n (car inList)) nil) 
					(DeleteMN (+ (cntInL (car inList) 0) (+ idx 1)) m n (cdr inList))
			)
		)
		(
			(= idx m) 
		    (DeleteMN (+ idx 1) m n (cdr inList))
		)
		(
			(= idx n)
			(DeleteMN (+ idx 1) m n (cdr inList))
		)
		(
			t
			(cons 
				(car inList) (DeleteMN (+ idx 1) m n (cdr inList))
			)
		)
	)
)

(defun cntInL(inList sum)
	(cond
		(
			(atom inList)
			sum
		)
		(
			(eq (atom (car inList)) nil)
			(+ (cntInL (car inList) 0) (cntInL (cdr inList) sum))
		)
		(
			t
			(cntInL (cdr inList) (+ sum 1))
		)
	)
)