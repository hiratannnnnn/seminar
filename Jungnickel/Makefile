all: lib euler

lib:
	$(MAKE) -C lib

euler:
	$(MAKE) -C euler

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C euler clean

fclean:	delres
	$(MAKE) -C lib fclean
	$(MAKE) -C euler fclean

delres:
	find . -name "result_*" -exec rm -rf {} +
	find . -name "results_*" -exec rm -rf {} +
	find . -name "*.out" -exec rm -f {} +
	find . -name "*.exe" -exec rm -f {} +
	find . -name "*_graph.txt" -exec rm -f {} +
	find . -name "*_list.txt" -exec rm -f {} +
	find . -name "*_path.txt" -exec rm -f {} +

re: fclean all

.PHONY: all lib euler clean fclean re
