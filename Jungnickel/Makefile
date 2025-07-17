DIRS = lib path

all: archives

archives:
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir archive; \
	done
	@ls -la dist/

clean:
	@for dir in $(DIRS); do $(MAKE) -C $$dir clean; done

distclean:
	@rm -rf dist

fclean:	delres distclean
	@for dir in $(DIRS); do $(MAKE) -C $$dir fclean; done

delres:
	@find . -name "result_*" -exec rm -rf {} +
	@find . -name "results_*" -exec rm -rf {} +
	@find . -name "*.out" -exec rm -f {} +
	@find . -name "*.exe" -exec rm -f {} +
	@find . -name "*_graph.txt" -exec rm -f {} +
	@find . -name "*_list.txt" -exec rm -f {} +
	@find . -name "*_path.txt" -exec rm -f {} +

re: fclean all

.PHONY: all $(DIRS) clean fclean re delres
